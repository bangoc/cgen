/* (C) Nguyễn Bá Ngọc 2023 */

#include "base/flog.h"
#include "cont/vector.h"

struct vector *create_perm(long n) {
  if (n < 1) {
    FLOG("Tạo hoán vị với tham số không hợp lệ.");
    return NULL;
  }
  struct vector *v = vcreate(n);
  if (!v) {
    FLOG("Lỗi tạo vec-tơ");
    return NULL;
  }
  long i = 0;
  VTRAVERSE(cur, v) {
    cur->l = i++;
  }
  return v;
}

struct vector *next_perm(struct vector *v) {
  long k = vsize(v) - 1;
  gtype *a = varr(v);
  while (k > 0) {
    if (a[k - 1].l < a[k].l) {
      break;
    }
    --k;
  }
  if (k == 0) {
    return NULL;
  }
  long i = k - 1, l = vsize(v) - 1;
  while (a[l].l < a[i].l) {
    --l;
  }
  GSWAP(a[l], a[i]);
  l = vsize(v) - 1;
  while (k < l) {
    GSWAP(a[k], a[l]);
    ++k;
    --l;
  }
  return v;
}

struct vector *prev_perm(struct vector *v) {
  long k = vsize(v) - 1;
  gtype *a = varr(v);
  while (k > 0) {
    if (a[k - 1].l > a[k].l) {
      break;
    }
    --k;
  }
  if (k == 0) {
    return NULL;
  }
  long i = k - 1, l = vsize(v) - 1;
  while (a[l].l > a[i].l) {
    --l;
  }
  GSWAP(a[i], a[l]);
  l = vsize(v) - 1;
  while (k < l) {
    GSWAP(a[k], a[l]);
    ++k;
    --l;
  }
  return v;
}

int has_next_perm(struct vector *v) {
  long k = vsize(v) - 1;
  gtype *a = varr(v);
  while (k > 0) {
    if (a[k - 1].l < a[k].l) {
      return 1;
    }
  }
  return 0;
}

int has_prev_perm(struct vector *v) {
  long k = vsize(v) - 1;
  gtype *a = varr(v);
  while (k > 0) {
    if (a[k - 1].l > a[k].l) {
      return 1;
    }
  }
  return 0;
}