/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef SVEC_H_
#define SVEC_H_

#include "vv.h"
#include <string.h>

static int svec_push_back(vector_t *v, char *s) {
  char *dup = strdup(s);
  return vv_push_back(v, dup);
}

static void svec_free(vector_t *v) {
  for (int i = 0; i < vv_size(*v); ++i) {
    free((*v)[i]);
  }
  vv_free(v);
  *v = 0;
}

#endif  // SVEC_H_