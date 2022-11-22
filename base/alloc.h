/* (C) Nguyen Ba Ngoc 2022 */

#ifndef BASE_ALLOC_H_
#define BASE_ALLOC_H_

#include <stddef.h>
#include <string.h>

#ifdef CGEN_USE_GC

typedef void *malloc_fnt(size_t sz);
typedef void *calloc_fnt(size_t nmem, size_t sz);
typedef void *realloc_fnt(void *ptr, size_t sz);
typedef char *strdup_fnt(const char *s);

extern malloc_fnt *cgen_malloc;
extern calloc_fnt *cgen_calloc;
extern realloc_fnt *cgen_realloc;
extern strdup_fnt *cgen_strdup;

void *cgen_calloc_wrapper(size_t nmem, size_t sz);

char *cgen_strdup_wrapper(const char *s);

void cgen_gc_init(malloc_fnt *m, calloc_fnt *c, realloc_fnt *re);

#endif  // CGEN_USE_GC

#endif  // BASE_ALLOC_H_