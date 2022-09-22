/* (C) Nguyen Ba Ngoc 2022 */

#include "algo/sort.h"

#include <limits.h>


/* Giá trị bí ẩn, ngưỡng chuyển sang xếp chèn */
#define QUICKSORT_THRESH 10

struct stack_node {
  gtype *lo;
  gtype *hi;
};

#define QS_STACK_SIZE  (CHAR_BIT * sizeof(size_t))
#define QS_PUSH(low, high)  ((void) ((top->lo = (low)), (top->hi = (high)), ++top))
#define QS_POP(low, high)  ((void) (--top, (low = top->lo), (high = top->hi)))
#define QS_STACK_NOT_EMPTY  (stack < top)

void quicksort(long n, gtype *a, gtype_cmp_t cmp) {
  if (n <= 0) {
    return;
  }
  if (n > QUICKSORT_THRESH) {
    gtype *lo = a;
    gtype *hi = a + n - 1;
    struct stack_node stack[QS_STACK_SIZE];
    struct stack_node *top = stack;
    QS_PUSH(NULL, NULL);

    while (QS_STACK_NOT_EMPTY) {
      gtype *left_ptr;
      gtype *right_ptr;

      /* Tìm số trung vị của LO, MID, và HI */
      gtype *mid = lo + ((hi - lo) >> 1);

      if (cmp(*mid, *lo) < 0) {
        gtype_swap(*mid, *lo);
      }
      if (cmp(*hi, *mid) < 0) {
        gtype_swap(*hi, *mid);
        if (cmp(*mid, *lo) < 0) {
          gtype_swap(*mid, *lo);
        }
      }
      left_ptr = lo + 1;
      right_ptr = hi - 1;
      gtype v = *mid;
      do {
        while (cmp(v, *left_ptr) > 0) ++left_ptr;
        while (cmp(*right_ptr, v) > 0) --right_ptr;
        if (left_ptr < right_ptr) {
          gtype_swap(*left_ptr, *right_ptr);
          ++left_ptr;
          --right_ptr;
        } else if (left_ptr == right_ptr) {
          ++left_ptr;
          --right_ptr;
          break;
        }
      } while (left_ptr <= right_ptr);

      if (right_ptr - lo <= QUICKSORT_THRESH) {
        if (hi - left_ptr <= QUICKSORT_THRESH) {
          QS_POP(lo, hi);
        } else {
          lo = left_ptr;
        }
      } else if (hi - left_ptr <= QUICKSORT_THRESH) {
        hi = right_ptr;
      } else if (right_ptr - lo > hi - left_ptr) {
        QS_PUSH(lo, right_ptr);
        lo = left_ptr;
      } else {
        QS_PUSH(left_ptr, hi);
        hi = right_ptr;
      }
    }
  }

  // Sắp xếp chèn
  {
    long thresh = n - 1;
    if (thresh > QUICKSORT_THRESH) {
      thresh = QUICKSORT_THRESH;
    }
    long i, j = 0;
    for (i = 1; i <= thresh; ++i) {
      if (cmp(a[i], a[j]) < 0) {
        j = i;
      }
    }
    if (j != 0) {
      gtype_swap(a[0], a[j]);
    }
    for (i = 2; i < n; ++i) {
      gtype c = a[i];
      j = i;
      while (cmp(a[j - 1], c) > 0) {
        a[j] = a[j - 1];
        --j;
      }
      a[j] = c;
    }
  }
}

#undef QUICKSORT_THRESH
#undef QS_STACK_SIZE
#undef QS_PUSH
#undef QS_POP
#undef QS_STACK_NOT_EMPTY