#ifndef HMAP_H_
#define HMAP_H_

/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "arr.h"
#include "gtype.h"
#include "hfunc.h"

#include <stdint.h>

typedef uint (*gtype_hash_t) (gtype);

typedef struct hash_map {
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

hmap_t hmap_create(gtype_hash_t hash_func, gtype_cmp_t cmp,
          gtype_free_t key_free, gtype_free_t value_free);
int hmap_insert(hmap_t tab, gtype key, gtype value);
gtype *hmap_value(hmap_t tab, gtype key);
int hmap_remove(hmap_t tab, gtype key);
void hmap_clear(hmap_t tab);
void hmap_free(hmap_t tab);
int hmap_nnodes(hmap_t tab);



#endif  // HMAP_H_