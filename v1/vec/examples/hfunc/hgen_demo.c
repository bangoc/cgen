/* (C) Nguyen Ba Ngoc 2021 */

/**
 * Minh họa hàm băm khái quát
 */

#include "all.h"

#include <stdio.h>
#include <string.h>

#define DEMO_S(str) \
  do { \
    const char * _s = str; \
    printf("hgen(\"%s\") = %lu\n", _s, (unsigned long)hgen(_s, strlen(_s))); \
  } while (0)

#define DEMO_D(value) \
  do {\
    double _d = value; \
    printf("hgen(%f) = %lu\n", _d, (unsigned long)hgen(&_d, sizeof _d)); \
  } while (0)

#define DEMO_L(value) \
  do { \
    long _l = value; \
    printf("hgen(%ld) = %lu\n", _l, (unsigned long)hgen(&_l, sizeof _l)); \
  } while (0)

int main() {
  DEMO_S("Hello world!");
  DEMO_S("Hello");
  DEMO_S("world!");
  DEMO_S("Xuân đi, Xuân đến");
  DEMO_D(3.1415);
  DEMO_D(2.54);
  DEMO_D(2.);
  DEMO_L(-101);
  DEMO_L(101);
  DEMO_L(1001);
  return 0;
}