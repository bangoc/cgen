/* Nguyễn Bá Ngọc 2023 */

#ifndef ALGO_ALGO_H_
#define ALGO_ALGO_H_

#include "base/fnt.h"
#include <stdlib.h>

static inline void vswap(void *o1, void *o2, int sz) {
  char tmp, *p = o1, *q = o2;
  for (int i = 0; i < sz; ++i) {
    tmp = *p;
    *p = *q;
    *q = tmp;
    ++p;
    ++q;
  }
}

static void q2sort(void *a, int n, int sz, compare_fnt cmp) {
  if (n <= 1) {
    return;
  }
  void *left = a, *right = a + (n - 2) * sz;
  void *v = a + (n - 1) * sz;
  for (;;) {
    while (cmp(v, left) > 0) {
      left += sz;
    }
    while (cmp(right, v) > 0) {
      if (right == a) {
        break;
      }
      right -= sz;
    }
    if (left >= right) {
      break;
    }
    vswap(left, right, sz);
    left += sz;
    right -= sz;
  }
  vswap(left, v, sz);
  right = left + sz;
  left = left - sz;
  q2sort(a, (left - a)/sz + 1, sz, cmp);
  q2sort(right, (a - right)/sz + n, sz, cmp);
}

static int binsearch(const void *a, int n, int sz, const void *v, compare_fnt cmp) {
  int l = 0, r = n - 1;
  while (l <= r) {
    int m = (l + r) / 2;
    int x = cmp(a + m * sz, v);
    if (x == 0) {
      return m;
    }
    if (x < 0) {
      l = m + 1;
    } else if (x > 0) {
      r = m - 1;
    }
  }
  return -1;
}

#define HTOP(i) (((i) - 1) >> 1)
#define HLEFT(i) (((i) << 1) + 1)
#define HRIGHT(i) (((i) << 1) + 2)

static void heap_shift_down(void *a, int n, int sz, int i, compare_fnt cmp) {
  for (;;) {
    int lc = HLEFT(i), rc = HRIGHT(i), top = i;
    if (lc < n && cmp(a + top * sz, a + lc * sz) < 0) {
      top = lc;
    }
    if (rc < n && cmp(a + top * sz, a + rc * sz) < 0) {
      top = rc;
    }
    if (top == i) {
      break;
    }
    vswap(a + i * sz, a + top * sz, sz);
    i = top;
  }
}

void heap_shift_up(void *a, int n, int sz, int i, compare_fnt cmp) {
  int j = HTOP(i);
  while (i > 0 && cmp(a + j * sz, a + i * sz) < 0) {
    vswap(a + i * sz, a + j * sz, sz);
    i = j;
    j = HTOP(i);
  }
}

static void heap_make(void *a, int n, int sz, compare_fnt cmp) {
  for (int i = n / 2; i >= 0; --i) {
    heap_shift_down(a, n, sz, i, cmp);
  }
}

static int *first_perm(int n) {
  int *a = malloc((n + 1) * sizeof(int));
  a[0] = n;
  for (int i = 1; i <= n; ++i) {
    a[i] = i - 1;
  }
  return a + 1;
}

static int next_perm(int *a) {
  int n = a[-1], k = n -1;
  while (k > 0) {
    if (a[k - 1] < a[k]) {
      break;
    }
    --k;
  }
  if (k == 0) {
    return 0;
  }
  int i = k - 1, l = n - 1;
  while (a[l] < a[i]) {
    --l;
  }
  int tmp = a[l];
  a[l] = a[i];
  a[i] = tmp;
  l = n - 1;
  while (k < l) {
    tmp = a[k];
    a[k] = a[l];
    a[l] = tmp;
    ++k;
    --l;
  }
  return 1;
}

static int has_next_perm(int *a) {
  int n = a[-1], k = n -1;
  while (k > 0) {
    if (a[k - 1] < a[k]) {
      return 1;
    }
    --k;
  }
  return 0;
}

static void free_perm(int *a) {
  --a;
  free(a);
}

#endif  // ALGO_ALGO_H_