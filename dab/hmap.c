/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "dab/hmap.h"

#include <stdio.h>
#include <stdlib.h>

static void hmap_setup_storage(hmap_t tab);
static inline int hmap_lookup_node(hmap_t tab, gtype key, uint *hash_return);
static inline int hmap_maybe_realloc(hmap_t tab);
static void hmap_remove_node(hmap_t tab, int i);

hmap_t hmap_create(gtype_hash_t hash_func, gtype_cmp_t cmp,
          gtype_free_t free_key, gtype_free_t free_value) {
  hmap_t tab = malloc(sizeof(struct hash_map));
  tab->size = 0;
  tab->noccupied = 0;
  tab->hash_func = hash_func;
  tab->cmp = cmp;
  tab->free_key = free_key;
  tab->free_value = free_value;
  hmap_setup_storage(tab);
  return tab;
}

void gtype_free_hmap(gtype value) {
  hmap_free(value.hmap);
}

gtype *hmap_value(hmap_t tab, gtype key) {
  int node_index = hmap_lookup_node(tab, key, NULL);
  return (HASH_IS_REAL(elem(tab->hashes, node_index)))?
          &elem(tab->values, node_index): NULL;
}

hmap_ires hmap_insert(hmap_t tab, gtype key, gtype value) {
  uint *hashes = ARR(tab->hashes);
  gtype *values = ARR(tab->values);
  uint key_hash;
  int node_index = hmap_lookup_node(tab, key, &key_hash);
  uint curr_hash = hashes[node_index];
  int already_exists = HASH_IS_REAL(curr_hash);
  if (already_exists) {
    return (hmap_ires){values + node_index, 0};
  }
  hashes[node_index] = key_hash;
  ARR(tab->keys)[node_index] = key;
  values[node_index] = value;
  tab->size++;
  if (HASH_IS_UNUSED(curr_hash)) {
    tab->noccupied++;
    if (hmap_maybe_realloc(tab) == 1) {
      node_index = hmap_lookup_node(tab, key, NULL);
      values = ARR(tab->values);
    }
  }
  return (hmap_ires){values + node_index, 1};
}

gtype *hmap_put(hmap_t tab, gtype key, gtype value) {
  uint *hashes = ARR(tab->hashes);
  gtype *values = ARR(tab->values);
  uint key_hash;
  int node_index = hmap_lookup_node(tab, key, &key_hash);
  uint curr_hash = hashes[node_index];
  int already_exists = HASH_IS_REAL(curr_hash);
  if (already_exists) {
    return values + node_index;
  }
  hashes[node_index] = key_hash;
  ARR(tab->keys)[node_index] = key;
  values[node_index] = value;
  tab->size++;
  if (HASH_IS_UNUSED(curr_hash)) {
    tab->noccupied++;
    hmap_maybe_realloc(tab);
  }
  return NULL;
}

int hmap_remove(hmap_t tab, gtype key) {
  int node_index = hmap_lookup_node(tab, key, NULL);
  if (HASH_IS_NOTREAL(elem(tab->hashes, node_index))) {
    return 0;
  }
  hmap_remove_node(tab, node_index);
  hmap_maybe_realloc(tab);
  return 1;
}

void hmap_clear(hmap_t tab) {
  int capacity = (tab)->capacity;
  gtype *keys = ARR((tab)->keys);
  gtype *values = ARR((tab)->values);
  uint *hashes = ARR((tab)->hashes);
  for (int i = 0; i < capacity; ++i) {
    if (HASH_IS_REAL(hashes[i])) {
      if ((tab)->free_key) {
        (tab)->free_key(keys[i]);
      }
      if ((tab)->free_value) {
        (tab)->free_value(values[i]);
      }
    }
  }
  tab->size = 0;
  tab->noccupied = 0;
  arr_set_size((tab)->keys, 0);
  arr_set_size((tab)->values, 0);
  arr_set_size((tab)->hashes, 0);
  memset(ARR((tab)->hashes), 0, (tab)->capacity * sizeof(uint));
  hmap_maybe_realloc(tab);
}

gtype *hmap_next_pkey(hmap_t map, gtype* curr) {
  gtype * r;
  hashes_next_pkey_or_pvalue(map, curr, keys, r);
  return r;
}

gtype *hmap_next_pvalue(hmap_t map, gtype* curr) {
  gtype * r;
  hashes_next_pkey_or_pvalue(map, curr, values, r);
  return r;
}

static void hmap_set_shift(hmap_t tab, int shift) {
  tab->capacity = 1 << shift;
  tab->mod = prime_mod[shift];
  tab->mask = tab->capacity - 1;
}

static int hmap_find_closest_shift(int n) {
  int i = 0;
  for (; n; ++i) {
    n >>= 1;
  }
  return i;
}

static void hmap_set_shift_from_capacity(hmap_t tab, int capacity) {
  int shift = hmap_find_closest_shift(capacity);
  shift = MAX(shift, HASH_MIN_SHIFT);
  hmap_set_shift(tab, shift);
}

#define hmap_hash_to_index(tab, hash)((hash * 11) % tab->mod)

static void hmap_setup_storage(hmap_t tab) {
  hmap_set_shift(tab, HASH_MIN_SHIFT);
  tab->hashes = arr_create(tab->capacity, uint);
  memset(ARR(tab->hashes), 0, tab->capacity * sizeof(uint));
  tab->keys = arr_create(tab->capacity, gtype);
  tab->values = arr_create(tab->capacity, gtype);
}

static inline int hmap_lookup_node(hmap_t tab, gtype key, uint *hash_return) {
  uint lookup_hash = tab->hash_func(key);
  if (HASH_IS_NOTREAL(lookup_hash)) {
    lookup_hash = MIN_HASH_VALUE;
  }
  if (hash_return) {
    *hash_return = lookup_hash;
  }
  uint *hashes = ARR(tab->hashes);
  gtype *keys = ARR(tab->keys);
  int node_index = hmap_hash_to_index(tab, lookup_hash);
  uint node_hash = hashes[node_index];
  int first_deleted = -1;
  int step = 0;
  while (HASH_IS_INUSED(node_hash)) {
    if (node_hash == lookup_hash) {
      gtype node_key = keys[node_index];
      if (tab->cmp(node_key, key) == 0) {
        return node_index;
      }
    } else if (HASH_IS_DELETED(node_hash) && first_deleted < 0) {
      first_deleted = node_index;
    }
    ++step;
    node_index += step;
    node_index &= tab->mask;
    node_hash = hashes[node_index];
  }
  if (first_deleted >= 0) {
    return first_deleted;
  }
  return node_index;
}

static void hmap_remove_node(hmap_t tab, int i) {
  gtype key = elem(tab->keys, i), value = elem(tab->values, i);
  elem(tab->hashes, i) = DELETED_HASH_VALUE;
  tab->size--;
  if (tab->free_key) {
    tab->free_key(key);
  }
  if (tab->free_value) {
    tab->free_value(value);
  }
}

static void hmap_realloc_arrays(hmap_t tab) {
  arr_set_capacity(tab->hashes, tab->capacity);
  arr_set_capacity(tab->keys, tab->capacity);
  arr_set_capacity(tab->values, tab->capacity);
}

static void relocate_map(hmap_t tab, uint old_capacity, uint32 *reallocated_buckets_bitmap) {
  uint *hashes = ARR(tab->hashes);
  gtype *keys = ARR(tab->keys);
  gtype *values = ARR(tab->values);
  for (int i = 0; i < old_capacity; ++i) {
    uint node_hash = hashes[i];
    gtype key, value;
    if (HASH_IS_NOTREAL(node_hash)) {
      hashes[i] = UNUSED_HASH_VALUE;
      continue;
    }
    if (get_status_bit(reallocated_buckets_bitmap, i)) {
      continue;
    }
    hashes[i] = UNUSED_HASH_VALUE;
    key = keys[i];
    value = values[i];
    for (;;) {
      uint idx, replaced_hash, step = 0;
      idx = hmap_hash_to_index(tab, node_hash);
      while (get_status_bit(reallocated_buckets_bitmap, idx)) {
        ++step;
        idx += step;
        idx &= tab->mask;
      }
      set_status_bit(reallocated_buckets_bitmap, idx);
      replaced_hash = hashes[idx];
      hashes[idx] = node_hash;
      if (HASH_IS_NOTREAL(replaced_hash)) {
        keys[idx] = key;
        values[idx] = value;
        break;
      }
      node_hash = replaced_hash;
      evict_key_or_value(keys, idx, key, key);
      evict_key_or_value(values, idx, value, value);
    }
  }
}

static void hmap_realloc(hmap_t tab) {
  uint32 *reallocated_buckets_bitmap;
  int old_capacity;
  old_capacity = tab->capacity;
  hmap_set_shift_from_capacity(tab, tab->size * 1.333);
  if (tab->capacity > old_capacity) {
    hmap_realloc_arrays(tab);
    memset(ARR(tab->hashes) + old_capacity, 0, (tab->capacity - old_capacity) * sizeof(uint));
    reallocated_buckets_bitmap = calloc((tab->capacity + 31) / 32, sizeof(uint32));
  } else {
    reallocated_buckets_bitmap = calloc((old_capacity + 31) / 32, sizeof(uint32));
  }

  relocate_map(tab, old_capacity, reallocated_buckets_bitmap);
  free(reallocated_buckets_bitmap);
  if (tab->capacity < old_capacity) {
    hmap_realloc_arrays(tab);
  }
  tab->noccupied = tab->size;
}

static inline int hmap_maybe_realloc(hmap_t tab) {
  uint noccupied = tab->noccupied, capacity = tab->capacity;
  if ((capacity > tab->size * 4 && capacity > 1 << HASH_MIN_SHIFT) ||
      (capacity <= noccupied + (noccupied/16))) {
    hmap_realloc(tab);
    return 1;
  }
  return 0;
}
