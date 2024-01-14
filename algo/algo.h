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

static void *binsearch(const void *k, void *a, int n, int sz, compare_fnt cmp) {
  int l = 0, r = n - 1, m, o;
  while (l <= r) {
    m = (l + r) / 2;
    o = cmp(k, a + m * sz);
    if (o == 0) {
      return a + m * sz;
    }
    if (o < 0) {
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return NULL;
}

static void *bnear_search(const void *k, void *a, int n, int sz, compare_fnt cmp) {
  int l = 0, r = n - 1, m = 0, o;
  while (l <= r) {
    m = (l + r) / 2;
    o = cmp(k, a + m * sz);
    if (o == 0) {
      break;
    }
    if (o < 0) {
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return a + m * sz;
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

static void heap_shift_up(void *a, int n, int sz, int i, compare_fnt cmp) {
  int top = HTOP(i);
  while (i > 0 && cmp(a + top * sz, a + i * sz) < 0) {
    vswap(a + i * sz, a + top * sz, sz);
    i = top;
    top = HTOP(top);
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
  ++a;
  for (int i = 0; i < n; ++i) {
    a[i] = i;
  }
  return a;
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
  free(a - 1);
}

static int *first_comb(int k, int n) {
  if (k > n || k < 1) {
    return NULL;
  }
  int *a = malloc((k + 2) * sizeof(int));
  a[0] = k;
  a[1] = n;
  a += 2;
  for (int i = 0; i < k; ++i) {
    a[i] = i;
  }
  return a;
}

static int next_comb(int *a) {
  int k = a[-2], n = a[-1], r = k - 1;
  while (r >= 0) {
    if (a[r] < n - k + r) {
      ++a[r];
      for (int i = r + 1; i < k; ++i) {
        a[i] = a[i - 1] + 1;
      }
      return 1;
    }
    --r;
  }
  return 0;
}

static int has_next_comb(int *a) {
  int k = a[-2], n = a[-1], r = k - 1;
  while (r >= 0) {
    if (a[r] < n - k + r) {
      return 1;
    }
    --r;
  }
  return 0;
}

static void free_comb(int *a) {
  free(a - 2);
}

#endif  // ALGO_ALGO_H_