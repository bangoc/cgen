/* (C) Nguyen Ba Ngoc 2022 */


#include "base/alloc.h"

#include <stdlib.h>

malloc_fnt *ext_malloc = malloc;
calloc_fnt *ext_calloc = calloc;
realloc_fnt *ext_realloc = realloc;
strdup_fnt *ext_strdup = strdup;
free_fnt *ext_free = free;

void *calloc_malloc_based(size_t nmem, size_t sz) {
  if (!nmem) {
    return calloc_malloc_based(1, sz);
  }
  void *ptr = ext_malloc(nmem * sz);
  memset(ptr, 0, nmem * sz);
  return ptr;
}

char *strdup_malloc_based(const char *s) {
  size_t len = strlen(s);
  char *ptr = ext_malloc(len + 1);
  strcpy(ptr, s);
  return ptr;
}
