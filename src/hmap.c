/*
  (C) Nguyen Ba Ngoc 2o21
*/

#include "hmap.h"

#include <stdio.h>
#include <stdlib.h>

#define HMAP_MIN_SHIFT 3
#define UNUSED_HASH_VALUE 0
#define DELETED_HASH_VALUE 1
#define MIN_HASH_VALUE 2
#define HASH_IS_UNUSED(h_) ((h_) == UNUSED_HASH_VALUE)
#define HASH_IS_INUSED(h_) (!HASH_IS_UNUSED(h_))
#define HASH_IS_DELETED(h_) ((h_) == DELETED_HASH_VALUE)
#define HASH_IS_REAL(h_) ((h_) >= MIN_HASH_VALUE)
#define HASH_IS_NOTREAL(h_) (!HASH_IS_REAL(h_))
#define MAX(a, b) (a > b? a: b)

static void hmap_setup_storage(hmap_t tab);
static inline int hmap_lookup_node(hmap_t tab, gtype key, uint *hash_return);
static inline void hmap_maybe_resize(hmap_t tab);
static void hmap_remove_node(hmap_t tab, int i);
static void hmap_free_nodes(hmap_t tab);

hmap_t hmap_create(gtype_hash_t hash_func, gtype_cmp_t cmp,
          gtype_free_t key_free, gtype_free_t value_free) {
  hmap_t tab = malloc(sizeof(struct hash_map));
  tab->nnodes = 0;
  tab->noccupied = 0;
  tab->hash_func = hash_func;
  tab->cmp = cmp;
  tab->key_free = key_free;
  tab->value_free = value_free;
  hmap_setup_storage(tab);
  return tab;
}

gtype *hmap_value(hmap_t tab, gtype key) {
  int node_index = hmap_lookup_node(tab, key, NULL);
  return (HASH_IS_REAL(ELEM(tab->hashes, node_index)))?
          &ELEM(tab->values, node_index): NULL;
}

int hmap_insert(hmap_t tab, gtype key, gtype value) {
  uint *hashes = ARR(tab->hashes);
  gtype *keys = ARR(tab->keys);
  gtype *values = ARR(tab->values);
  uint key_hash;
  int node_index = hmap_lookup_node(tab, key, &key_hash);
  uint curr_hash = hashes[node_index];
  int already_exists = HASH_IS_REAL(curr_hash);
  if (already_exists) {
    if (tab->key_free) {
      tab->key_free(key);
    }
    if (tab->value_free) {
      tab->value_free(values[node_index]);
    }
    values[node_index] = value;
    return node_index;
  }
  hashes[node_index] = key_hash;
  keys[node_index] = key;
  values[node_index] = value;
  tab->nnodes++;
  if (HASH_IS_UNUSED(curr_hash)) {
    tab->noccupied++;
    hmap_maybe_resize(tab);
  }
  return node_index;
}

int hmap_remove(hmap_t tab, gtype key) {
  int node_index = hmap_lookup_node(tab, key, NULL);
  if (HASH_IS_NOTREAL(ELEM(tab->hashes, node_index))) {
    return 0;
  }
  hmap_remove_node(tab, node_index);
  hmap_maybe_resize(tab);
  return 1;
}

void hmap_clear(hmap_t tab) {
  hmap_free_nodes(tab);
  hmap_setup_storage(tab);
}

void hmap_free(hmap_t tab) {
  hmap_free_nodes(tab);
  free(tab);
}

int hmap_nnodes(hmap_t tab) {
  return tab->nnodes;
}

static const int prime_mod [] =
{
  1,          /* 1 << 0 */
  2,
  3,
  7,
  13,
  31,
  61,
  127,
  251,
  509,
  1021,
  2039,
  4093,
  8191,
  16381,
  32749,
  65521,      /* 1 << 16 */
  131071,
  262139,
  524287,
  1048573,
  2097143,
  4194301,
  8388593,
  16777213,
  33554393,
  67108859,
  134217689,
  268435399,
  536870909,
  1073741789,
  2147483647  /* 1 << 31 */
};

static void hmap_set_shift(hmap_t tab, int shift) {
  tab->size = 1 << shift;
  tab->mod = prime_mod[shift];
  tab->mask = tab->size - 1;
}

static int hmap_find_closest_shift(int n) {
  int i = 0;
  for (; n; ++i) {
    n >>= 1;
  }
  return i;
}

static void hmap_set_shift_from_size(hmap_t tab, int size) {
  int shift = hmap_find_closest_shift(size);
  shift = MAX(shift, HMAP_MIN_SHIFT);
  hmap_set_shift(tab, shift);
}

#define hmap_hash_to_index(tab, hash)((hash * 11) % tab->mod)

static void hmap_setup_storage(hmap_t tab) {
  hmap_set_shift(tab, HMAP_MIN_SHIFT);
  tab->keys = arr_create(tab->size, gtype);
  tab->values = arr_create(tab->size, gtype);
  tab->hashes = arr_create(tab->size, uint);
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
  gtype key = ELEM(tab->keys, i), value = ELEM(tab->values, i);
  ELEM(tab->hashes, i) = DELETED_HASH_VALUE;
  tab->nnodes--;
  if (tab->key_free) {
    tab->key_free(key);
  }
  if (tab->value_free) {
    tab->value_free(value);
  }
}

static void hmap_free_nodes(hmap_t tab) {
  if (tab->nnodes ==0) {
    return;
  }
  int size = tab->size;
  gtype *keys = ARR(tab->keys);
  gtype *values = ARR(tab->values);
  uint *hashes = ARR(tab->hashes);
  for (int i = 0; i < size; ++i) {
    if (HASH_IS_REAL(hashes[i])) {
      if (tab->key_free) {
        tab->key_free(keys[i]);
      }
      if (tab->value_free) {
        tab->value_free(values[i]);
      }
    }
  }
  arr_free(tab->keys);
  arr_free(tab->values);
  arr_free(tab->hashes);

  tab->nnodes = 0;
  tab->noccupied = 0;
}

static void realloc_arrays(hmap_t tab) {
  arr_set_size(tab->hashes, tab->size);
  arr_set_size(tab->keys, tab->size);
  arr_set_size(tab->values, tab->size);
}

#define get_status_bit(bitmap, index) ((bitmap[index/32] >> (index %32)) & 1)
#define set_status_bit(bitmap, index) (bitmap[index / 32] |= 1U << (index % 32))

#define evict_key_or_value(a, i, v, ov) \
  { \
    gtype tmp = a[i]; \
    a[i] = v; \
    ov = tmp; \
  }

static void resize_map(hmap_t tab, uint old_size, uint32 *reallocated_buckets_bitmap) {
  uint *hashes = ARR(tab->hashes);
  gtype *keys = ARR(tab->keys);
  gtype *values = ARR(tab->values);
  for (int i = 0; i < old_size; ++i) {
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

static void hmap_resize(hmap_t tab) {
  uint32 *reallocated_buckets_bitmap;
  int old_size;
  old_size = tab->size;
  hmap_set_shift_from_size(tab, tab->nnodes * 1.333);
  if (tab->size > old_size) {
    realloc_arrays(tab);
    memset(ARR(tab->hashes) + old_size, 0, (tab->size - old_size) * sizeof(uint));
    reallocated_buckets_bitmap = calloc((tab->size + 31) / 32, sizeof(uint32));
  } else {
    reallocated_buckets_bitmap = calloc((old_size + 31) / 32, sizeof(uint32));
  }

  resize_map(tab, old_size, reallocated_buckets_bitmap);
  free(reallocated_buckets_bitmap);
  if (tab->size < old_size) {
    realloc_arrays(tab);
  }
  tab->noccupied = tab->nnodes;
}

static inline void hmap_maybe_resize(hmap_t tab) {
  uint noccupied = tab->noccupied, size = tab->size;
  if ((size > tab->nnodes * 4 && size > 1 << HMAP_MIN_SHIFT) ||
      (size <= noccupied + (noccupied/16))) {
    hmap_resize(tab);
  }
}
