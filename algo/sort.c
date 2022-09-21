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

void q2sort(long n, gtype *a, gtype_cmp_t cmp) {
  if (n <= 1) {
    return;
  }
  gtype *left = a, *right = a + n - 2;
  gtype v = a[n - 1];
  for (;;) {
    while (cmp(v, *left) > 0) {
      ++left;
    }
    while (cmp(*right, v) > 0) {
      if (right == a) {
        break;
      }
      --right;
    }
    if (left >= right) {
      break;
    }
    swap(*left, *right);
    ++left;
    --right;
  }
  swap(*left, a[n - 1]);
  right = left + 1;
  left = left - 1;
  q2sort(left - a + 1, a, cmp);
  q2sort(a + n - right, right, cmp);
}

void q3sort(long n, gtype *a, gtype_cmp_t cmp) {
  if (n <= 1) {
    return;
  }
  gtype *left = a, *right = a + n - 2;
  gtype v = a[n - 1];
  gtype *p = a, *q = a + n - 2;
  for (;;) {
    while (cmp(v, *left) > 0) {
      ++left;
    }
    while (cmp(*right, v) > 0) {
      if (right == a) {
        break;
      }
      --right;
    }
    if (left >= right) {
      break;
    }
    swap(*left, *right);
    if (cmp(*left, v) == 0) {
      swap(*p, *left);
      ++p;
    }
    if (cmp(*right, v) == 0) {
      swap(*q, *right);
      --q;
    }
    ++left;
    --right;
  }
  swap(*left, a[n - 1]);
  right = left + 1;
  left = left - 1;
  for (gtype *k = a; k < p; ++k, --left) {
    swap(*k, *left);
  }
  for (gtype *k = a + n - 2; k > q; --k, ++right) {
    swap(*k, *right);
  }
  q3sort(left - a + 1, a, cmp);
  q3sort(a + n - right, right, cmp);
}