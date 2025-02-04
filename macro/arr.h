/* (C) Nguyen Ba Ngoc 2025 */

#ifndef ARR_H_
#define ARR_H_

#include <stdlib.h>

/**
 * Mảng động cải tiến, có ghi nhớ số lượng phần tử
 */

static inline void *arr_alloc(int nmem, int size) {
  int *tmp = malloc(sizeof(int) + nmem * size);
  *tmp = nmem;
  return tmp + 1;
}

static inline void *arr_realloc(void *a, int nmem, int size) {
  int *tmp = a - sizeof(int);
  tmp = realloc(tmp, sizeof(int) + nmem * size);
  *tmp = nmem;
  return tmp + 1;
}

#define arr(elem_t, n) \
  arr_alloc(n, sizeof(elem_t))

#define arr_cap(a) \
  *((int *)(a) - 1)

#define arr_reserve(a, cap) \
  ((a) = arr_realloc(a, cap, sizeof(a[0])))

#define arr_for(a, i) \
  for (int i = 0; i < arr_cap(a); ++i)

#define arr_rfor(a, i) \
  for (int i = arr_cap(a) - 1; i >= 0; --i)

void arr_free(void *a) {
  int *tmp = a - sizeof(int);
  free(tmp);
}

#endif  // ARR_H_
