/* (C) Nguyen Ba Ngoc 2022 */

#include "base/alloc.h"

#include <stdlib.h>

#ifdef CGEN_USE_GC

const int cgen_use_gc = 1;

malloc_fnt *ext_malloc = NULL;
calloc_fnt *ext_calloc = cgen_calloc_wrapper;
realloc_fnt *ext_realloc = NULL;
strdup_fnt *ext_strdup = cgen_strdup_wrapper;

void *cgen_calloc_wrapper(size_t nmem, size_t sz) {
  if (!nmem) {
    return ext_malloc(sz);
  }
  void *ptr = ext_malloc(nmem * sz);
  memset(ptr, 0, nmem * sz);
  return ptr;
}

char *cgen_strdup_wrapper(const char *s) {
  size_t len = strlen(s);
  char *ptr = ext_malloc(len + 1);
  strcpy(ptr, s);
  return ptr;
}

void cgen_alloc_set_base(malloc_fnt *m, realloc_fnt *re) {
  ext_malloc = m;
  ext_realloc = re;
}

#else  // CGEN_USE_GC

const int cgen_use_gc = 0;

#endif  // CGEN_USE_GC