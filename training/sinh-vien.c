/* (C) Nguyễn Bá Ngọc 2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sinh_vien {
  int stt;
  char mssv[10];
  char hoten[101];
  float hp;
};

typedef struct sinh_vien vec_elem_t;

struct vector {
  int sz;
  int cap;
  vec_elem_t *elems;
};

#define VFOR(v, cur) for (vec_elem_t* cur = (v)->elems; cur < (v)->elems + (v)->sz; ++cur)

void vprint_elem(vec_elem_t *e) {
  printf("%d,%s,%s,%.1f", e->stt, e->mssv, e->hoten, e->hp);
}

void vscan_elem(vec_elem_t *e) {
  scanf("%d%*c%[^,]%*c%[^,]%*c%f",
        &e->stt, e->mssv, e->hoten, &e->hp);
}

struct vector *vcreate(int n) {
  struct vector *v = malloc(sizeof(struct vector));
  v->sz = n;
  v->cap = v->sz > 0? v->sz: 8;
  v->elems = calloc(v->cap, sizeof(vec_elem_t));
  return v;
}

void vreserve(struct vector *v, int newcap) {
  if (newcap <= v->sz) {
    return;
  }
  v->elems = realloc(v->elems, newcap * sizeof(vec_elem_t));
  if (v->cap < newcap) {
    memset(v->elems + v->cap, 0, sizeof(vec_elem_t) * (newcap - v->cap));
  }
  v->cap = newcap;
}

void vappend(struct vector *v, vec_elem_t value) {
  if (v->cap == 0) {
    vreserve(v, 16);
  } else if (v->sz == v->cap) {
    vreserve(v, 2 * v->cap);
  }
  v->elems[v->sz] = value;
  ++v->sz;
}

void vresize(struct vector *v, int newsize) {
  if (newsize > v->cap) {
    vreserve(v, newsize);
  }
  v->sz = newsize;
}

void vfree(struct vector *v) {
  if (!v) {
    return;
  }
  free(v->elems);
  free(v);
}

struct vector *vparse_nlist() {
  int n;
  scanf("%d", &n);
  struct vector *v = vcreate(n);
  VFOR(v, cur) {
    vscan_elem(cur);
  }
  return v;
}

int failed_count(struct vector *v) {
  int cc = 0;
  VFOR(v, cur) {
    if (cur->hp < 4) {
      ++cc;
    }
  }
  return cc;
}

vec_elem_t *first_max_hp(struct vector *v) {
  vec_elem_t *p = NULL;
  float max = -1;
  VFOR(v, cur) {
    if (max < cur->hp) {
      max = cur->hp;
      p = cur;
    }
  }
  return p;
}

void solve() {
  struct vector *v = vparse_nlist();
  int fc = failed_count(v);
  printf("%d\n", fc);
  printf("%d\n", v->sz - fc);
  vprint_elem(first_max_hp(v));
  vfree(v);
}

int main() {
  solve();
}