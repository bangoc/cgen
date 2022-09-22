/* (C) Nguyen Ba Ngoc 2022 */

#include "sort.h"

#include "vec/heap.h"

void heapsort(long n, gtype *a, gtype_cmp_t cmp) {
  heap_make(n, a, cmp);
  for (long i = n - 1; i > 0; --i) {
    gtype_swap(a[0], a[i]);
    heap_shift_down(0, i, a, cmp);
  }
}