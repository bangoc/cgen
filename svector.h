/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef SVECTOR_H_
#define SVECTOR_H_

#include "gtvector.h"
#include <string.h>
#include <stdio.h>

// ========== Khai báo hàm ===============
static int svec_push_back(vector_t *v, char *s);
static void svec_free(vector_t *v);

// ========== Macro viết nhanh ===========


// ========== Định nghĩa hàm =============

static int svec_push_back(vector_t *v, char *s) {
  char *dup = strdup(s);
  return gtv_push_back(v, (gtype){.s = dup});
}

static void svec_free(vector_t *v) {
  for (int i = 0; i < gtv_size(*v); ++i) {
    free((*v)[i].s);
  }
  gtv_free(v);
  *v = 0;
}

static void svec_print(vector_t v) {
  printf("size = %lld, capacity = %lld, elements:\n",
        (long long)gtv_size(v), (long long)gtv_capacity(v));
  for (int i = 0; i < gtv_size(v); ++i) {
    printf("%d: %s\n", i, v[i].s);
  }
}

#endif  // SVECTOR_H_