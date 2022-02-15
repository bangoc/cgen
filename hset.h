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

typedef struct hash_set {
  int capacity;
  int mod;
  uint mask;
  int size;
  int noccupied;
  arr_t(gtype) keys;
  arr_t(uint) hashes;
  gtype_hash_t hash_func;
  gtype_cmp_t cmp;
  gtype_free_t free_key;
} *hset_t;

#define hset_hash_at(set, idx) (elem_ref((set)->hashes, idx))
#define hset_key_at(set, idx) (elem_ref((set)->keys, idx))
#define INDEX_NOT_FOUND -1
#define hset_contains(hs, value) (hset_index_of(hs, value) != INDEX_NOT_FOUND)

hset_t hset_create(gtype_hash_t hash_func, gtype_cmp_t cmp,
          gtype_free_t free_key);
int hset_insert(hset_t hs, gtype key);
int hset_index_of(hset_t hs, gtype key);
int hset_remove(hset_t hs, gtype key);
void hset_clear(hset_t hs);
void hset_free(hset_t hs);
/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng hset
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới hset.
 * Trước tiên value.v được ép kiểu thành hset_t, sau đó con trỏ hset_t
 * được truyền cho hset_free.
 * @return Hàm không trả về giá trị.
 */
void hset_gtype_free(gtype value);

#define hset_size(hs) (hs->size)

gtype *hset_next_pkey(hset_t, gtype*);
#define hset_traverse(key, map) \
  for(gtype *key = hset_next_pkey(map, NULL); \
     key; key = hset_next_pkey(map, key)) \

#endif  // HSET_H_