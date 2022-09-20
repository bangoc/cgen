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

void insort(long n, gtype *a, gtype_cmp_t cmp) {
  // a[0] == min
  for (int i = n - 1; i > 0; --i) {
    if (cmp(a[i - 1], a[i]) > 0) {
      swap(a[i - 1], a[i]);
    }
  }
  for (int i = 2; i < n; ++i) {
    int j = i;
    gtype v = a[i];
    while (cmp(a[j - 1], v) > 0) {
      a[j] = a[j - 1];
      --j;
    }
    a[j] = v;
  }
}

void bubsort(long n, gtype *a, gtype_cmp_t cmp) {
  for (int i = 0; i < n - 1; ++i) {
    for (int j = n - 1; j > i; --j) {
      if (cmp(a[j - 1], a[j]) > 0) {
        swap(a[j - 1], a[j]);
      }
    }
  }
}