#ifndef BASE_HASHES_H_
#define BASE_HASHES_H_

#include "base/gtype.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
  Triển khai hmap và hset
*/
#define HASH_MIN_SHIFT 3
#define UNUSED_HASH_VALUE 0
#define DELETED_HASH_VALUE 1
#define MIN_HASH_VALUE 2
#define HASH_IS_UNUSED(h_) ((h_) == UNUSED_HASH_VALUE)
#define HASH_IS_INUSED(h_) (!HASH_IS_UNUSED(h_))
#define HASH_IS_DELETED(h_) ((h_) == DELETED_HASH_VALUE)
#define HASH_IS_REAL(h_) ((h_) >= MIN_HASH_VALUE)
#define HASH_IS_NOTREAL(h_) (!HASH_IS_REAL(h_))
#define MAX(a, b) ((a) > (b)? (a): (b))

typedef unsigned int uint;
typedef uint32_t uint32;
typedef uint (*gtype_hash_t) (gtype);

#define hashes_next_pkey_or_pvalue(m, c, kv, o) \
  do { \
    (o) = NULL; \
    int _idx = (c)? (c) - (m)->kv + 1: 0; \
    for (int _i = _idx; _i < (m)->capacity; ++_i) { \
      if (HASH_IS_REAL((m)->hashes[_i])) { \
        (o) = (m)->kv + _i; \
        break; \
      } \
    } \
  } while (0)

extern const int prime_mod [];

#define get_status_bit(bitmap, index) (((bitmap)[(index)/32] >> ((index) %32)) & 1)
#define set_status_bit(bitmap, index) ((bitmap)[(index) / 32] |= 1U << ((index) % 32))

#define evict_key_or_value(a, i, v, ov) \
  { \
    gtype _tmp = (a)[(i)]; \
    (a)[(i)] = (v); \
    (ov) = _tmp; \
  }

// Một hàm băm khái quát
static uint32_t hgen(const void *data, long length) {
  register long i = length;
  register uint32_t hv = 0;
  register const unsigned char *s = (const unsigned char *)data;
  while (i--) {
    hv += *s++;
    hv += (hv << 10);
    hv ^= (hv >> 6);
  }
  hv += (hv << 3);
  hv ^= (hv >> 11);
  hv += (hv << 15);

  return hv;
}

static inline uint gtype_hash_s(gtype v) {
  const char *p;
  uint h = 5381;
  for (p = v.s; *p != '\0'; ++p) {
    h = (h << 5) + h + *p;
  }
  return h;
}

static inline uint gtype_hash_d(gtype v) {
  return (uint) v.d;
}

static inline uint gtype_hash_l(gtype v) {
  return (uint) v.l;
}

#ifdef __cplusplus
}
#endif

#endif  // BASE_HASHES_H_