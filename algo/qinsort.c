/* (C) Nguyen Ba Ngoc */

#include "sort.h"

#define Q2M3_THRESH 8

static void _q2m3thresh(long n, gtype *a, gtype_cmp_t cmp) {
  if (n <= Q2M3_THRESH) {
    return;
  }
  gtype *left = a, *right = a + n - 1,
        *mid = left + ((right - left) >> 1);
  if (cmp(*left, *mid) > 0) {
    gtype_swap(*left, *mid);
  }
  if (cmp(*mid, *right) > 0) {
    gtype_swap(*mid, *right);
    if (cmp(*left, *mid) > 0) {
      gtype_swap(*left, *mid);
    }
  }
  ++left;
  --right;
  gtype v = *mid;
  do {
    while (cmp(v, *left) > 0) {
      ++left;
    }
    while (cmp(*right, v) > 0) {
      --right;
    }
    if (left < right) {
      gtype_swap(*left, *right);
      ++left;
      --right;
    } else if (left == right) {
      ++left;
      --right;
    }
  } while (left <= right);
  _q2m3thresh(right - a + 1, a, cmp);
  _q2m3thresh(a + n - left, left, cmp);
}

void qinsort(long n, gtype *a, gtype_cmp_t cmp) {
  _q2m3thresh(n, a, cmp);
  insort(n, a, cmp);
}

#undef Q2M3_THRESH