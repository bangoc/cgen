/* (C) Nguyen Ba Ngoc 2022 */

#ifndef BASE_ALLOC_H_
#define BASE_ALLOC_H_

#include <stddef.h>
#include <string.h>

typedef void *malloc_fnt(size_t sz);
typedef void *calloc_fnt(size_t nmem, size_t sz);
typedef void *realloc_fnt(void *ptr, size_t sz);
typedef char *strdup_fnt(const char *s);
typedef void free_fnt(void *ptr);

extern malloc_fnt *ext_malloc;
extern calloc_fnt *ext_calloc;
extern realloc_fnt *ext_realloc;
extern strdup_fnt *ext_strdup;
extern free_fnt *ext_free;

void *calloc_malloc_based(size_t nmem, size_t sz);
char *strdup_malloc_based(const char *s);

#define cgen_set_malloc(fn) ext_malloc = fn
#define cgen_set_calloc(fn) ext_calloc = fn
#define cgen_set_realloc(fn) ext_realloc = fn
#define cgen_set_strdup(fn) ext_strdup = fn
#define cgen_set_free(fn) ext_free = fn

#define cgen_heap_manager(malloc, calloc, realloc, strdup, free) \
  cgen_set_malloc(malloc); \
  cgen_set_calloc(calloc); \
  cgen_set_realloc(realloc); \
  cgen_set_strdup(strdup); \
  cgen_set_free(free)

#endif  // BASE_ALLOC_H_