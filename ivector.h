/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef IVEC_H_
#define IVEC_H_

#include "gtvector.h"
#include <string.h>

// ========== Khai báo hàm ===============
static int ivec_push_back(vector_t *v, long value);
static void svec_free(vector_t *v);

// ========== Macro viết nhanh ===========


// ========== Định nghĩa hàm =============

static int ivec_push_back(vector_t *v, long value) {
  return gtv_push_back(v, (gtype){.i = value});
}

static void svec_free(vector_t *v) {
  gtv_free(v);
  *v = 0;
}

#endif  // SVEC_H_