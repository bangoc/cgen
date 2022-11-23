/* (C) Nguyen Ba Ngoc 2022 */

#include "base/alloc.h"

#include <stdlib.h>

#ifndef CGEN_USE_GC

const int cgen_use_gc = 0;

malloc_fnt *ext_malloc = malloc;
calloc_fnt *ext_calloc = calloc;
realloc_fnt *ext_realloc = realloc;
strdup_fnt *ext_strdup = strdup;
free_fnt *ext_free = free;

#else  // CGEN_USE_GC

const int cgen_use_gc = 1;
// tgc_t gc;

malloc_fnt *ext_malloc = GC_malloc;
calloc_fnt *ext_calloc = malloc_based_calloc;
realloc_fnt *ext_realloc = GC_realloc;
strdup_fnt *ext_strdup = malloc_based_strdup;
free_fnt *ext_free = cgen_noop_free;

void *malloc_based_calloc(size_t nmem, size_t sz) {
  if (!nmem) {
    return malloc_based_calloc(1, sz);
  }
  void *ptr = ext_malloc(nmem * sz);
  memset(ptr, 0, nmem * sz);
  return ptr;
}

char *malloc_based_strdup(const char *s) {
  size_t len = strlen(s);
  char *ptr = ext_malloc(len + 1);
  strcpy(ptr, s);
  return ptr;
}

void cgen_alloc_set_base(malloc_fnt *m, realloc_fnt *re) {
  ext_malloc = m;
  ext_realloc = re;
}

// void *cgen_gc_malloc(size_t size) {
//   return tgc_alloc(&gc, size);
// }

// void *cgen_gc_calloc(size_t count, size_t size) {
//   return tgc_calloc(&gc, count, size);
// }

// void *cgen_gc_realloc(void* ptr, size_t size) {
//   return tgc_realloc(&gc, ptr, size);
// }

void cgen_noop_free(void *ptr) {}

#endif  // CGEN_USE_GC