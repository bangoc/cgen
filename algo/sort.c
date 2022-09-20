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

void q2sort(long l, long r, gtype *a, gtype_cmp_t cmp) {
  int i = l - 1, j = r;
  gtype v = a[r];
  for (;;) {
    while (cmp(v, a[++i]) > 0) ;
    while (j > l && cmp(a[--j], v) > 0) ;
    if (i >= j) {
      break;
    }
    swap(a[i], a[j]);
  }
  swap(a[i], a[r]);
  if (i - 1 > l) {
    q2sort(l, i - 1, a, cmp);
  }
  if (r > i + 1) {
    q2sort(i + 1, r, a, cmp);
  }
}

void q3sort(long l, long r, gtype *a, gtype_cmp_t cmp) {
  if (r <= l) {
    return;
  }
  gtype v = a[r];
  int i = l - 1, j = r, p = l - 1, q = r;
  for (;;) {
    while (cmp(v, a[++i]) > 0) ;
    while (cmp(a[--j], v) > 0) {
      if (j == l) {
        break;
      }
    }
    if (i >= j) {
      break;
    }
    swap(a[i], a[j]);
    if (cmp(a[i], v) == 0) {
      ++p;
      swap(a[p], a[i]);
    }
    if (cmp(a[j], v) == 0) {
      --q;
      swap(a[q], a[j]);
    }
  }
  swap(a[i], a[r]);
  j = i - 1;
  i = i + 1;
  for (int k = l; k < p; ++k, --j) {
    swap(a[k], a[j]);
  }
  for (int k = r - 1; k > q; --k, ++i) {
    swap(a[k], a[i]);
  }
  q3sort(l, j, a, cmp);
  q3sort(i, r, a, cmp);
}