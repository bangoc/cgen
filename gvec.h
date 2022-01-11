#ifndef GVEC_H_
#define GVEC_H_

/* (C) Nguyen Ba Ngoc 2021 */

/** @file
 * @brief Vec-tơ (mảng cấp phát động) của các giá trị gtype.
 *
 * Có thể truy cập ngẫu nhiên đến 1 phần tử bất kỳ trong vec-tơ
 * theo chỉ số và sắp xếp nhanh vec-tơ tương tự như mảng.
 * Tuy nhiên kích thước của vec-tơ có thể thay đổi sau khi được tạo
 * (dựa trên realloc) vì vậy linh động hơn mảng thông thường và
 * cũng có phạm vi ứng dụng rộng hơn.
 */

#include "base/arr.h"
#include "base/gtype.h"

/**
 * \headerfile "cgen.h"
 * Cấu trúc lưu các thông tin điều khiển vec-tơ.
 *
 * Các macros điều khiển:
 *
 *   #gvec_size(v) - Trả về size của vec-tơ.
 *
 *   #gvec_capacity(v) - Trả về capacity của vec-tơ.
 */
typedef struct gvec_s {
  /**
   * Mảng cơ sở lưu các đối tượng gtype
   */
  arr_t(gtype) arr;

  /**
   * Con trỏ tới hàm giải phóng dữ liệu được quản lý qua đối tượng
   * gtype trong mảng. Nếu != NULL thì hàm được gọi khi giải phóng
   * bộ nhớ của vec-tơ, nếu ngược lại (== NULL) thì các gọi hàm được
   * bỏ qua.
   */
  gtype_free_t free_value;
} *gvec_t;

/**
 * Hàm tạo đối tượng vec-tơ.
 *
 * @param cap (capacity) Dung lượng ban đầu của vec-tơ.
 * @param free_value con trỏ hàm giải phóng bộ nhớ bên ngoài đối tượng gtype.
 * Sử dụng NULL nếu không có bộ nhớ bên ngoài.
 *
 * \memberof gvec_s
 */
gvec_t gvec_create(int cap, gtype_free_t free_value);

/**
 * Trả về kích thước (size) của vec-tơ. Trong vec-tơ size là
 * số lượng phần tử mảng đã sử dụng, còn capacity là số lượng phần tử
 * đã cấp phát cho mảng cơ sở (arr), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 */
#define gvec_size(v) (arr_size((v)->arr))

/**
 * Trả về dung lượng (capacity) của vec-tơ. Trong vec-tơ size là
 * số lượng phần tử mảng đã sử dụng, còn capacity là số lượng phần tử
 * đã cấp phát cho mảng cơ sở (arr), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 */
#define gvec_capacity(v) (arr_capacity((v)->arr))
#define gvec_arr(v) (ARR((v)->arr))
#define gvec_elem(v, i) ((gvec_arr(v))[(i)])
#define gvec_elem_idx(v, elem) ((long)((elem) - gvec_arr(v)))

#define gvec_append(v, val) \
  do { \
    arr_append((v)->arr, val); \
  } while (0)

#define gvec_remove(v, idx) \
  do { \
    gtype *_arr = ARR((v)->arr); \
    int _sz = arr_size((v)->arr); \
    if ((idx) >= _sz || (idx) < 0) { \
      break; \
    } \
    if ((v)->free_value) { \
      (v)->free_value(_arr[(idx)]); \
    } \
    for (int _i = (idx); _i < _sz - 1; ++_i) { \
      _arr[_i] = _arr[_i + 1]; \
    } \
    arr_set_size((v)->arr, _sz - 1); \
  } while (0)

#define gvec_set_capacity(v, cap) \
  do { \
    int _sz = arr_size((v)->arr); \
    if ((cap) < _sz) { \
      break; \
    } \
    arr_set_capacity((v)->arr, (cap)); \
  }

#define gvec_free(v) \
  do{ \
    if ((v)->free_value) { \
      int _sz = arr_size((v)->arr); \
      gtype *_arr = ARR((v)->arr); \
      for (int _i = 0; _i < _sz; ++_i) { \
        (v)->free_value(_arr[_i]); \
      } \
    } \
    arr_free((v)->arr); \
    free(v); \
  } while (0)

#define gvec_qsort(v, cmp) \
  qsort(ARR((v)->arr), gvec_size(v), sizeof(gtype), cmp)

#define gvec_traverse(cur, v) \
  for (gtype *cur = gvec_arr(v), *end = gvec_arr(v) + gvec_size(v); cur < end; ++cur)

#endif  // GVEC_H_
