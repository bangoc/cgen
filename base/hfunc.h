#ifndef BASE_HFUNC_H_
#define BASE_HFUNC_H_

#include "base/gtype.h"

#ifdef __cplusplus
extern "C" {
#endif

// Một hàm băm khái quát
static uint32_t hgen(const void *data, long length) {
  register long i = length;
  register uint32_t hv = 0;
  register const unsigned char *s = data;
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

static uint gtype_hash_s(gtype v) {
  const signed char *p;
  uint h = 5381;
  for (p = v.s; *p != '\0'; ++p) {
    h = (h << 5) + h + *p;
  }
  return h;
}

static uint gtype_hash_d(gtype v) {
  return (uint) v.d;
}

static uint gtype_hash_i(gtype v) {
  return (uint) v.i;
}

#ifdef __cplusplus
}
#endif

#endif  // BASE_HFUNC_H_