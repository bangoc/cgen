#ifndef ALGO_SORT_H_
#define ALGO_SORT_H_

/* (C) Nguyen Ba Ngoc 2022 */

#include "base/gtype.h"

void selsort(long n, gtype *a, gtype_cmp_t cmp);
void insort(long n, gtype *a, gtype_cmp_t cmp);
void bubsort(long n, gtype *a, gtype_cmp_t cmp);

/* Sắp xếp nhanh, phân mảnh 2 phần */
void q2sort(long n, gtype *a, gtype_cmp_t cmp);

/* Sắp xếp nhanh, phân mảnh 2 phần, sử dụng trung vị của lo, mid, hi làm chốt */
void q2m3sort(long n, gtype *a, gtype_cmp_t cmp);

/* Kết hợp q2m3 và sắp xếp chèn */
void qinsort(long n, gtype *a, gtype_cmp_t cmp);

/* Sắp xếp nhanh, phân mảnh 3 phần */
void q3sort(long n, gtype *a, gtype_cmp_t cmp);

/**
 * Tùy chỉnh glibc cho gtype:
 * Phân mảnh 2 phần, sử dụng trung vị của lo, mid, hi,
 *   bỏ qua khối nhỏ, xếp chèn dãy gần hoàn thiện và khử đệ quy.
 */
void quicksort(long n, gtype *a, gtype_cmp_t cmp);

/**
 * Sắp xếp vun đống.
 */
void heapsort(long n, gtype *a, gtype_cmp_t cmp);

#endif  // ALGO_SORT_H_