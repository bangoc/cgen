#ifndef LEARNING_VEC_B02_SOLVE_H_
#define LEARNING_VEC_B02_SOLVE_H_

#include "base/gtype.h"

/**
 * Tìm phần tử nhỏ nhất trong 1 vec-tơ gtype, biết rằng
 * các phần tử chứa số nguyên kiểu long ở trường l.
 *
 * @param v Con trỏ tới vec-tơ.
 * @return Phần tử nhỏ nhất tìm được.
 */
gtype gvec_min_l(struct gvector *v);

/**
 * Tìm phần tử lớn nhất trong 1 vec-tơ gtype, biết rằng
 * các phần tử chứa số thực kiểu double ở trường d.
 *
 * @param v Con trỏ tới vec-tơ.
 * @return Phần tử lớn nhất tìm được.
 */
gtype gvec_max_d(struct gvector *v);


/**
 * Đảo ngược thứ tự các phần tử của 1 vec-tơ gtype.
 *
 * @param v Con trỏ tới vec-tơ gtype.
 * @return Hàm không trả về kết quả
 */
void gvec_revert(struct gvector *v);


#endif  // LEARNING_VEC_B02_SOLVE_H_