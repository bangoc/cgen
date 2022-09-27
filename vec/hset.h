#ifndef VEC_HSET_H_
#define VEC_HSET_H_

/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Tập hợp dựa trên hàm băm (hash hs)
 */

#include "base/gtype.h"
#include "base/hashes.h"
#include "vec/arr.h"

#include <stdint.h>

struct hset {
  int capacity;
  int mod;
  uint mask;
  int size;
  int noccupied;
  atype(gtype) *keys;
  atype(uint) *hashes;
  gtype_hash_t hash_func;
  gtype_cmp_t cmp;
  gtype_free_t free_key;
};

#define hset_hash_at(set, idx) ((set)->hashes[idx])
#define hset_key_at(set, idx) ((set)->keys[idx])
#define INDEX_NOT_FOUND -1
#define hset_contains(hs, value) (hset_index_of(hs, value) != INDEX_NOT_FOUND)

struct hset *hset_create(gtype_hash_t hash_func, gtype_cmp_t cmp,
          gtype_free_t free_key);
int hset_insert(struct hset *hs, gtype key);
int hset_index_of(struct hset *hs, gtype key);
int hset_remove(struct hset *hs, gtype key);
void hset_clear(struct hset *hs);
void hset_free(struct hset *hs);

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng hset
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới đối tượng hset.
 * Con trỏ value.hset (kiểu ::struct hset *) được truyền cho hset_free.
 * @return Hàm không trả về giá trị.
 */
void gtype_free_hset(gtype value);

#define hset_size(hs) (hs->size)

gtype *hset_next_pkey(struct hset *, gtype*);
#define hset_traverse(key, map) \
  for(gtype *key = hset_next_pkey(map, NULL); \
     key; key = hset_next_pkey(map, key)) \

#endif  // VEC_HSET_H_