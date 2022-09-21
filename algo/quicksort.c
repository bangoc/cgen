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
  if (n == 0) {
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
        swap(*mid, *lo);
      }
      if (cmp(*hi, *mid) < 0) {
        swap(*hi, *mid);
        if (cmp(*mid, *lo) < 0) {
          swap(*mid, *lo);
        }
      }
      left_ptr = lo + 1;
      right_ptr = hi - 1;
      do {
        while (cmp(*mid, *left_ptr) > 0) ++left_ptr;
        while (cmp(*right_ptr, *mid) > 0) --right_ptr;
        if (left_ptr < right_ptr) {
          swap(*left_ptr, *right_ptr);
          if (mid == left_ptr) {
            mid = right_ptr;
          } else if (mid == right_ptr) {
            mid = left_ptr;
          }
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

  #define QS_MIN(x, y) ((x) < (y)? (x): (y))
  {
    gtype *const end_ptr = a + n - 1;
    gtype *tmp_ptr = a;
    gtype *thresh = QS_MIN(end_ptr, a + QUICKSORT_THRESH);
    gtype *run_ptr;
    for (run_ptr = tmp_ptr + 1; run_ptr <= thresh; ++run_ptr) {
      if (cmp(*run_ptr, *tmp_ptr) < 0) {
        tmp_ptr = run_ptr;
      }
    }
    if (tmp_ptr != a) {
      swap(*tmp_ptr, *a);
    }

    /* Sắp xếp chèn */
    run_ptr = a + 1;
    while (++run_ptr <= end_ptr) {
      tmp_ptr = run_ptr - 1;
      while (cmp(*run_ptr, *tmp_ptr) < 0) {
        --tmp_ptr;
      }
      ++tmp_ptr;
      if (tmp_ptr != run_ptr) {
        gtype *trav = run_ptr + 1;
        while (--trav >= run_ptr) {
          gtype c = *trav;
          gtype *hi, *lo;
          for (hi = lo = trav; --lo >= tmp_ptr; hi = lo)
            *hi = *lo;
          *hi = c;
        }
      }
    }
  }
  #undef QS_MIN
}

#undef QUICKSORT_THRESH
#undef QS_STACK_SIZE
#undef QS_PUSH
#undef QS_POP
#undef QS_STACK_NOT_EMPTY