#ifndef HSET_H_
#define HSET_H_

/*
  (C) Nguyen Ba Ngoc 2021
  Tập hợp dựa trên hàm băm (hash hs)
*/

#include "base/arr.h"
#include "base/gtype.h"
#include "base/hashes.h"

#include <stdint.h>

typedef struct hash_set_s {
  int size;
  int mod;
  uint mask;
  int nnodes;
  int noccupied;
  arr_t(gtype) keys;
  arr_t(uint) hashes;
  gtype_hash_t hash_func;
  gtype_cmp_t cmp;
  gtype_free_t key_free;
} *hset_t;

typedef struct hset_insert_result {
  int idx;
  int inserted;
} hset_ires;

#define hset_hash_at(set, idx) (elem_ref(set->hashes, idx))
#define hset_key_at(set, idx) (elem_ref(set->keys, idx))
#define INDEX_NOT_FOUND -1
#define hset_contains(hs, value) (hset_index_of(hs, value) != INDEX_NOT_FOUND)

hset_t hset_create(gtype_hash_t hash_func, gtype_cmp_t cmp,
          gtype_free_t key_free);
hset_ires hset_insert(hset_t hs, gtype key);
int hset_index_of(hset_t hs, gtype key);
int hset_remove(hset_t hs, gtype key);
void hset_clear(hset_t hs);
void hset_free(hset_t hs);
int hset_nnodes(hset_t hs);

gtype *hset_next_pkey(hset_t, gtype*);
#define hset_traverse(key, value, map) \
  for(gtype *key = hmap_next_pkey(map, NULL); \
     key; key = hmap_next_pkey(map, key)) \

#endif  // HSET_H_