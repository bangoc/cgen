/* (C) Nguyen Ba Ngoc 2022 */

#ifndef BASE_ALLOC_H_
#define BASE_ALLOC_H_

#include <gc.h>
#include <stddef.h>
#include <string.h>

extern const int cgen_use_gc;
// extern tgc_t gc;

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

void *malloc_based_calloc(size_t nmem, size_t sz);
char *malloc_based_strdup(const char *s);

void *cgen_gc_malloc(size_t size);
void *cgen_gc_calloc(size_t count, size_t size);
void *cgen_gc_realloc(void* ptr, size_t size);
void cgen_noop_free(void *ptr);

/**
 * Thiết lập tập hàm cấp phát bộ nhớ cơ bản. Khởi tạo
 * ext_malloc và ext_realloc trong chế độ GC là bắt buộc.
 */
void cgen_alloc_set_base(malloc_fnt *m, realloc_fnt *re);

#endif  // BASE_ALLOC_H_