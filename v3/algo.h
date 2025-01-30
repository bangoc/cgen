/* (C) Nguyễn Bá Ngọc 2025 */

#ifndef ALGO_H_
#define ALGO_H_

static inline void vswap(void *o1, void *o2, int sz) {
  char tmp, *p = o1, *q = o2, *end = p + sz;
  for (; p < end; ++p, ++q) {
    tmp = *p;
    *p = *q;
    *q = tmp;
  }
}

static inline void vassign(void *dest, void *src, int sz) {
  char *d = dest, *s = src, *e = s + sz;
  for (; s < e; ++d, ++s) {
    *d = *s;
  }
}

static void insort(void *a, int n, int sz,
        int (*cmp)(const void *, const void *)) {
  char v[sz];
  for (int i = 1; i < n; ++i) {
    void *p = a + i * sz;
    vassign(v, p, sz);
    p -= sz;
    while (p >= a && cmp(p, v) > 0) {
      vassign(p + sz, p, sz);
      p -= sz;
    }
    vassign(p + sz, v, sz);
  }
}

static void q2insort(void *a, int n, int sz,
      int (*cmp)(const void *, const void *)) {
  if (n < 8) {
    insort(a, n, sz, cmp);
    return;
  }
  void *left = a, *right = a + (n - 1) * sz,
        *mid = left + ((n - 1) >> 1) * sz;
  if (cmp(left, mid) > 0) {
    vswap(left, mid, sz);
  }
  if (cmp(mid, right) > 0) {
    vswap(mid, right, sz);
    if (cmp(left, mid) > 0) {
      vswap(left, mid, sz);
    }
  }
  left += sz;
  right -= sz;
  char v[sz];
  vassign(v, mid, sz);
  do {
    while (cmp(left, v) < 0) {
      left += sz;
    }
    while (cmp(v, right) < 0) {
      right -= sz;
    }
    if (left < right) {
      vswap(left, right, sz);
      left += sz;
      right -= sz;
    } else if (left == right) {
      left += sz;
      right -= sz;
    }
  } while (left <= right);
  q2insort(a, (right - a) / sz + 1, sz, cmp);
  q2insort(left, n - (left - a) / sz, sz, cmp);
}

static void *binsearch(void *key, void *a, int n, int sz,
      int (*cmp)(const void *, const void *)) {
  int l = 0, r = n - 1;
  while (l <= r) {
    int m = (l + r) >> 1;
    void *p = a + m * sz;
    int tmp = cmp(key, p);
    if (tmp == 0) {
      return p;
    }
    if (tmp > 0) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return 0;
}

static void *binsearch_lte(void *key, void *a, int n, int sz,
      int (*cmp)(const void *, const void *)) {
  int l = 0, r = n - 1;
  while (l <= r) {
    int m = (l + r) >> 1;
    void *p = a + m * sz;
    int tmp = cmp(key, p);
    if (tmp == 0) {
      return p;
    }
    if (tmp > 0) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return r < 0? 0: a + r * sz;
}

static void *binsearch_gte(void *key, void *a, int n, int sz,
      int (*cmp)(const void *, const void *)) {
  int l = 0, r = n - 1;
  while (l <= r) {
    int m = (l + r)  >> 1;
    void *p = a + m * sz;
    int tmp = cmp(key, p);
    if (tmp == 0) {
      return p;
    }
    if (tmp > 0) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return l >= n? 0: a + l * sz;
}

#define TOP(i) (((i) - 1) >> 1)
#define LEFT(i) (((i) << 1) + 1)
#define RIGHT(i) (((i) << 1) + 2)

static void heap_shift_down(void *a, int n, int sz, int i,
    int (*cmp)(const void *, const void *)) {
  for (;;) {
    int lc = LEFT(i), rc = RIGHT(i), top = i;
    if (lc < n && cmp(a + top * sz, a + lc * sz) > 0) {
      top = lc;
    }
    if (rc < n && cmp(a + top * sz, a + rc * sz) > 0) {
      top = rc;
    }
    if (top == i) {
      break;
    }
    vswap(a + i * sz, a + top * sz, sz);
    i = top;
  }
}

static void heap_shift_up(void *a, int n, int sz, int i,
        int (*cmp)(const void *, const void *)) {
  int top = TOP(i);
  while (i > 0 && cmp(a + top * sz, a + i * sz) > 0) {
    vswap(a + i * sz, a + top * sz, sz);
    i = top;
    top = TOP(top);
  }
}

static void heapify(void *a, int n, int sz,
        int (*cmp)(const void *, const void *)) {
  for (int i = TOP(n - 1); i >= 0; --i) {
    heap_shift_down(a, n, sz, i, cmp);
  }
}

static void heapsort(void *a, int n, int sz,
        int (*cmp)(const void *, const void *)) {
  heapify(a, n, sz, cmp);
  for (int i = n - 1; i > 0; --i) {
    vswap(a, a + i * sz, sz);
    heap_shift_down(a, i, sz, 0, cmp);
  }
  char *i = a, *j = a + (n - 1) * sz;
  while (i < j) {
    vswap(i, j, sz);
    i += sz;
    j -= sz;
  }
}

#define VHEAPSORT(v, cmp) heapsort(v->elems, v->size, sizeof(v->elems[0]), cmp)
#define VQ2INSORT(v, cmp) q2insort(v->elems, v->size, sizeof(v->elems[0]), cmp)

#endif  // ALGO_H_
