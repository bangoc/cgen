#ifndef HM_H_
#define HM_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
  A generic hash function
*/

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

#ifdef __cplusplus
}
#endif

#endif  // HM_H_