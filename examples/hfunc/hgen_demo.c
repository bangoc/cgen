/*
  (C) Nguyen Ba Ngoc 2021
  Minh họa hàm băm khái quát
*/

#include "base/hashes.h"

#include <stdio.h>
#include <string.h>

#define DEMO_S(str) \
  do { \
    const char * s = str; \
    printf("hgen(\"%s\") = %lu\n", s, (unsigned long)hgen(s, strlen(s))); \
  } while (0)

#define DEMO_D(value) \
  do {\
    double d = value; \
    printf("hgen(%f) = %lu\n", d, (unsigned long)hgen(&d, sizeof d)); \
  } while (0)

#define DEMO_L(value) \
  do { \
    long l = value; \
    printf("hgen(%ld) = %lu\n", l, (unsigned long)hgen(&l, sizeof l)); \
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