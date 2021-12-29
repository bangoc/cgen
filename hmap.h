#ifndef HMAP_H_
#define HMAP_H_

/*
  (C) Nguyen Ba Ngoc 2021
  Ánh xạ dựa trên hàm băm (hash map)
*/

#include "base/arr.h"
#include "base/gtype.h"
#include "base/hashes.h"

#include <stdint.h>

typedef struct hash_map_s {
  int size;
  int mod;
  uint mask;
  int nnodes;
  int noccupied;
  arr_t(gtype) keys;
  arr_t(gtype) values;
  arr_t(uint) hashes;
  gtype_hash_t hash_func;
  gtype_cmp_t cmp;
  gtype_free_t key_free, value_free;
} *hmap_t;

typedef struct hmap_insert_result {
  int idx;
  int inserted;
} hmap_ires;

#define hmap_hash_at(map, idx) (elem_ref((map)->hashes, idx))
#define hmap_key_at(map, idx) (elem_ref((map)->keys, idx))
#define hmap_value_at(map, idx) (elem_ref((map)->values, idx))

hmap_t hmap_create(gtype_hash_t hash_func, gtype_cmp_t cmp,
          gtype_free_t key_free, gtype_free_t value_free);
hmap_ires hmap_insert(hmap_t tab, gtype key, gtype value);
gtype *hmap_value(hmap_t tab, gtype key);
int hmap_remove(hmap_t tab, gtype key);
void hmap_clear(hmap_t tab);
void hmap_free(hmap_t tab);
int hmap_nnodes(hmap_t tab);

gtype *hmap_next_pkey(hmap_t, gtype*);
gtype *hmap_next_pvalue(hmap_t, gtype*);
#define hmap_traverse(key, value, map) \
  for(gtype *key = hmap_next_pkey(map, NULL), *value = hmap_next_pvalue(map, NULL); \
     key && value; key = hmap_next_pkey(map, key), value = hmap_next_pvalue(map, value)) \

#endif  // HMAP_H_