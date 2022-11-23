/* (C) Nguyen Ba Ngoc 2022 */

#ifndef BASE_ALLOC_H_
#define BASE_ALLOC_H_

#include <stddef.h>
#include <string.h>

extern const int cgen_use_gc;

#ifdef CGEN_USE_GC

typedef void *malloc_fnt(size_t sz);
typedef void *calloc_fnt(size_t nmem, size_t sz);
typedef void *realloc_fnt(void *ptr, size_t sz);
typedef char *strdup_fnt(const char *s);

extern malloc_fnt *ext_malloc;
extern calloc_fnt *ext_calloc;
extern realloc_fnt *ext_realloc;
extern strdup_fnt *ext_strdup;

void *cgen_calloc_wrapper(size_t nmem, size_t sz);

char *cgen_strdup_wrapper(const char *s);

/**
 * Thiết lập tập hàm cấp phát bộ nhớ cơ bản. Khởi tạo
 * ext_malloc và ext_realloc trong chế độ GC là bắt buộc.
 */
void cgen_alloc_set_base(malloc_fnt *m, realloc_fnt *re);

#endif  // CGEN_USE_GC

#endif  // BASE_ALLOC_H_