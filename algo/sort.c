/* (C) Nguyen Ba Ngoc */

#include "algo/sort.h"

void selsort(long n, gtype *a, gtype_cmp_t cmp) {
  for (int i = 0; i < n - 1; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (cmp(a[i], a[j]) > 0) {
        swap(a[i], a[j]);
      }
    }
  }
}
