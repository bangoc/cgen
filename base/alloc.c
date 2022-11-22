/* (C) Nguyen Ba Ngoc 2022 */

#include "base/alloc.h"

#include <stdlib.h>

#ifdef CGEN_USE_GC

malloc_fnt *cgen_malloc = NULL;
calloc_fnt *cgen_calloc = cgen_calloc_wrapper;
realloc_fnt *cgen_realloc = NULL;
strdup_fnt *cgen_strdup = cgen_strdup_wrapper;

void *cgen_calloc_wrapper(size_t nmem, size_t sz) {
  if (!nmem) {
    return cgen_malloc(sz);
  }
  void *ptr = cgen_malloc(nmem * sz);
  memset(ptr, 0, nmem * sz);
  return ptr;
}

char *cgen_strdup_wrapper(const char *s) {
  size_t len = strlen(s);
  char *ptr = cgen_malloc(len + 1);
  strcpy(ptr, s);
  return ptr;
}

void cgen_gc_init(malloc_fnt *m, calloc_fnt *c, realloc_fnt *re) {
  cgen_malloc = m;
  cgen_calloc = c;
  cgen_realloc = re;
}

#endif  // CGEN_USE_GC