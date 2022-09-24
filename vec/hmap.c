/* (C) Nguyen Ba Ngoc 2021 */

#include "vec/hmap.h"

#include <stdio.h>
#include <stdlib.h>

static void hmap_setup_storage(struct hmap *tab);
static inline int hmap_lookup_node(struct hmap *tab, gtype key, uint *hash_return);
static inline int hmap_maybe_realloc(struct hmap *tab);
static void hmap_remove_node(struct hmap *tab, int i);

struct hmap *hmap_create(gtype_hash_t hash_func, gtype_cmp_t cmp,
          gtype_free_t free_key, gtype_free_t free_value) {
  struct hmap *tab = malloc(sizeof(struct hmap));
  tab->size = 0;
  tab->noccupied = 0;
  tab->hash_func = hash_func;
  tab->cmp = cmp;
  tab->free_key = free_key;
  tab->free_value = free_value;
  hmap_setup_storage(tab);
  return tab;
}

static void hmap_set_shift(struct hmap *tab, int shift) {
  tab->capacity = 1 << shift;
  tab->mod = prime_mod[shift];
  tab->mask = tab->capacity - 1;
}

static void hmap_setup_storage(struct hmap *tab) {
  hmap_set_shift(tab, HASH_MIN_SHIFT);
  tab->hashes = arr_create(tab->capacity, uint);
  memset(tab->hashes, 0, tab->capacity * sizeof(uint));
  tab->keys = arr_create(tab->capacity, gtype);
  tab->values = arr_create(tab->capacity, gtype);
}

void gtype_free_hmap(gtype value) {
  hmap_free(value.hmap);
}

gtype *hmap_value(struct hmap *tab, gtype key) {
  int node_index = hmap_lookup_node(tab, key, NULL);
  return (HASH_IS_REAL(tab->hashes[node_index]))?
          tab->values + node_index: NULL;
}

struct hmap_ires hmap_insert(struct hmap *tab, gtype key, gtype value) {
  uint key_hash;
  int node_index = hmap_lookup_node(tab, key, &key_hash);
  uint curr_hash = tab->hashes[node_index];
  int already_exists = HASH_IS_REAL(curr_hash);
  if (already_exists) {
    return (struct hmap_ires){tab->values + node_index, 0};
  }
  tab->hashes[node_index] = key_hash;
  tab->keys[node_index] = key;
  tab->values[node_index] = value;
  tab->size++;
  if (HASH_IS_UNUSED(curr_hash)) {
    tab->noccupied++;
    if (hmap_maybe_realloc(tab) == 1) {
      node_index = hmap_lookup_node(tab, key, NULL);
    }
  }
  return (struct hmap_ires){tab->values + node_index, 1};
}

gtype *hmap_put(struct hmap *tab, gtype key, gtype value) {
  uint key_hash;
  int node_index = hmap_lookup_node(tab, key, &key_hash);
  uint curr_hash = tab->hashes[node_index];
  int already_exists = HASH_IS_REAL(curr_hash);
  if (already_exists) {
    return tab->values + node_index;
  }
  tab->hashes[node_index] = key_hash;
  tab->keys[node_index] = key;
  tab->values[node_index] = value;
  tab->size++;
  if (HASH_IS_UNUSED(curr_hash)) {
    tab->noccupied++;
    hmap_maybe_realloc(tab);
  }
  return NULL;
}

int hmap_remove(struct hmap *tab, gtype key) {
  int node_index = hmap_lookup_node(tab, key, NULL);
  if (HASH_IS_NOTREAL(tab->hashes[node_index])) {
    return 0;
  }
  hmap_remove_node(tab, node_index);
  hmap_maybe_realloc(tab);
  return 1;
}

void hmap_clear(struct hmap *tab) {
  int capacity = (tab)->capacity;
  for (int i = 0; i < capacity; ++i) {
    if (HASH_IS_REAL(tab->hashes[i])) {
      if (tab->free_key) {
        tab->free_key(tab->keys[i]);
      }
      if (tab->free_value) {
        tab->free_value(tab->values[i]);
      }
    }
  }
  tab->size = 0;
  tab->noccupied = 0;
  arr_resize(tab->keys, 0);
  arr_resize(tab->values, 0);
  arr_resize(tab->hashes, 0);
  memset(tab->hashes, 0, tab->capacity * sizeof(uint));
  hmap_maybe_realloc(tab);
}

gtype *hmap_next_pkey(struct hmap *map, gtype* curr) {
  gtype * r;
  hashes_next_pkey_or_pvalue(map, curr, keys, r);
  return r;
}

gtype *hmap_next_pvalue(struct hmap *map, gtype* curr) {
  gtype * r;
  hashes_next_pkey_or_pvalue(map, curr, values, r);
  return r;
}

static int hmap_find_closest_shift(int n) {
  int i = 0;
  for (; n; ++i) {
    n >>= 1;
  }
  return i;
}

static void hmap_set_shift_from_capacity(struct hmap *tab, int capacity) {
  int shift = hmap_find_closest_shift(capacity);
  shift = MAX(shift, HASH_MIN_SHIFT);
  hmap_set_shift(tab, shift);
}

#define hmap_hash_to_index(tab, hash)((hash * 11) % tab->mod)

static inline int hmap_lookup_node(struct hmap *tab, gtype key, uint *hash_return) {
  uint lookup_hash = tab->hash_func(key);
  if (HASH_IS_NOTREAL(lookup_hash)) {
    lookup_hash = MIN_HASH_VALUE;
  }
  if (hash_return) {
    *hash_return = lookup_hash;
  }
  int node_index = hmap_hash_to_index(tab, lookup_hash);
  uint node_hash = tab->hashes[node_index];
  int first_deleted = -1;
  int step = 0;
  while (HASH_IS_INUSED(node_hash)) {
    if (node_hash == lookup_hash) {
      gtype node_key = tab->keys[node_index];
      if (tab->cmp(node_key, key) == 0) {
        return node_index;
      }
    } else if (HASH_IS_DELETED(node_hash) && first_deleted < 0) {
      first_deleted = node_index;
    }
    ++step;
    node_index += step;
    node_index &= tab->mask;
    node_hash = tab->hashes[node_index];
  }
  if (first_deleted >= 0) {
    return first_deleted;
  }
  return node_index;
}

static void hmap_remove_node(struct hmap *tab, int i) {
  gtype key = tab->keys[i], value = tab->values[i];
  tab->hashes[i] = DELETED_HASH_VALUE;
  tab->size--;
  if (tab->free_key) {
    tab->free_key(key);
  }
  if (tab->free_value) {
    tab->free_value(value);
  }
}

static void hmap_realloc_arrays(struct hmap *tab) {
  arr_reserve(tab->hashes, tab->capacity);
  arr_reserve(tab->keys, tab->capacity);
  arr_reserve(tab->values, tab->capacity);
}

static void relocate_map(struct hmap *tab, uint old_capacity, uint32 *reallocated_buckets_bitmap) {
  for (int i = 0; i < old_capacity; ++i) {
    uint node_hash = tab->hashes[i];
    gtype key, value;
    if (HASH_IS_NOTREAL(node_hash)) {
      tab->hashes[i] = UNUSED_HASH_VALUE;
      continue;
    }
    if (get_status_bit(reallocated_buckets_bitmap, i)) {
      continue;
    }
    tab->hashes[i] = UNUSED_HASH_VALUE;
    key = tab->keys[i];
    value = tab->values[i];
    for (;;) {
      uint idx, replaced_hash, step = 0;
      idx = hmap_hash_to_index(tab, node_hash);
      while (get_status_bit(reallocated_buckets_bitmap, idx)) {
        ++step;
        idx += step;
        idx &= tab->mask;
      }
      set_status_bit(reallocated_buckets_bitmap, idx);
      replaced_hash = tab->hashes[idx];
      tab->hashes[idx] = node_hash;
      if (HASH_IS_NOTREAL(replaced_hash)) {
        tab->keys[idx] = key;
        tab->values[idx] = value;
        break;
      }
      node_hash = replaced_hash;
      evict_key_or_value(tab->keys, idx, key, key);
      evict_key_or_value(tab->values, idx, value, value);
    }
  }
}

static void hmap_realloc(struct hmap *tab) {
  uint32 *reallocated_buckets_bitmap;
  int old_capacity;
  old_capacity = tab->capacity;
  hmap_set_shift_from_capacity(tab, tab->size * 1.333);
  if (tab->capacity > old_capacity) {
    hmap_realloc_arrays(tab);
    memset(tab->hashes + old_capacity, 0, (tab->capacity - old_capacity) * sizeof(uint));
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

static inline int hmap_maybe_realloc(struct hmap *tab) {
  uint noccupied = tab->noccupied, capacity = tab->capacity;
  if ((capacity > tab->size * 4 && capacity > 1 << HASH_MIN_SHIFT) ||
      (capacity <= noccupied + (noccupied/16))) {
    hmap_realloc(tab);
    return 1;
  }
  return 0;
}
