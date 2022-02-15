#ifndef GVEC_H_
#define GVEC_H_

/* (C) Nguyen Ba Ngoc 2021 */

/** @file
 * @brief Vec-tơ (còn được gọi là mảng động) của các giá trị ::gtype.
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
 * Cấu trúc biểu diễn vec-tơ của các giá trị ::gtype.
 *
 * Các macros điều khiển:
 *
 *   #gvec_size(v) - Kích thước của v.
 *
 *   #gvec_capacity(v) - Dung lượng của v.
 *
 *   #gvec_arr(v) - Mảng các phần tử của v.
 *
 *   #gvec_elem(v, i) - Phần tử thứ i của v.
 *
 *   #gvec_idx_of(v, elem_ptr) - Chỉ số của phần tử được trỏ tới bởi
 *   elem_ptr trong v.
 *
 *   #gvec_append(v, val) - Thêm val vào sau phần tử cuối cùng trong v.
 *
 *   #gvec_remove(v, idx) - Xóa phần tử có chỉ số idx khỏi v.
 *
 *   #gvec_set_capacity(v, cap) - Chủ động thiết lập dung lượng cho v.
 *
 *   #gvec_free(v) - Giải phóng bộ nhớ được cấp phát cho v.
 *
 *   #gvec_qsort(v, cmp) - Sắp xếp các phần tử của v bằng qsort với hàm so sánh cmp.
 *
 *   #gvec_traverse(cur, v) - Duyệt các phần tử của v theo chiều thuận.
 */
typedef struct gvec_s {
  /**
   * Mảng cơ sở lưu các đối tượng ::gtype
   */
  arr_t(gtype) arr;

  /**
   * Con trỏ tới hàm giải phóng dữ liệu được quản lý qua đối tượng
   * ::gtype trong mảng. Nếu != NULL thì hàm được gọi khi giải phóng
   * bộ nhớ của vec-tơ, nếu ngược lại (== NULL) thì các gọi hàm được
   * bỏ qua.
   */
  gtype_free_t free_value;
} *gvec_t;

/**
 * Hàm tạo đối tượng vec-tơ.
 *
 * @param cap (capacity) Dung lượng ban đầu của vec-tơ.
 * @param free_value con trỏ hàm giải phóng bộ nhớ bên ngoài được gắn
 * với đối tượng ::gtype. Sử dụng NULL nếu không có bộ nhớ bên ngoài.
 * @return Trả về đối tượng tạo được nếu thành công hoặc NULL_PTR nếu thất bại.
 * \memberof gvec_s
 */
gvec_t gvec_create(int cap, gtype_free_t free_value);

/**
 * Trong vec-tơ size là số lượng phần tử mảng đã sử dụng,
 * còn capacity là số lượng phần tử đã được cấp phát cho
 * mảng cơ sở (arr), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 * @return Trả về kích thước (size) của vec-tơ, giá trị có kiểu long.
 */
#define gvec_size(v) (arr_size((v)->arr))

/**
 * Trong vec-tơ size là số lượng phần tử mảng đã sử dụng,
 * còn capacity là số lượng phần tử đã được cấp phát cho
 * mảng cơ sở (arr), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 * @return Trả về dung lượng (capacity) của vec-tơ, giá trị có kiểu long.
 */
#define gvec_capacity(v) (arr_capacity((v)->arr))

/**
 * Giao diện mảng của vec-tơ.
 * \code{.c}
 * gvec_arr(v)[0];  \\ Phần tử đầu tiên của vec-tơ v.
 * \endcode
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 * @return Trả về con trỏ tới phần tử đầu tiên của mảng (kiểu ::gtype *)
 */
#define gvec_arr(v) (ARR((v)->arr))

/**
 * Chỉ định phần tử của vec-tơ bằng chỉ số.
 * \code{.c}
 *  gvec_elem(v, 0);  \\ Phần tử đầu tiên của vec-tơ v.
 * \endcode
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 * @param i Chỉ số của phần tử, là số nguyên và < #gvec_size(v).
 * @return Phần tử có chỉ số i trong vec-tơ v, kết quả là lvalue có kiểu ::gtype.
 */
#define gvec_elem(v, i) ((gvec_arr(v))[(i)])

/**
 * Chỉ số của phần tử trong vec-tơ.
 * \code{.c}
 * gvec_idx_of(&gvec_elem(v, i)) == i;
 * \endcode
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 * @param elem_ptr Con trỏ tới 1 phần tử hợp lệ trong vec-tơ.
 * @return Chỉ số của phần tử được trỏ tới bởi elem_ptr.
 */
#define gvec_idx_of(v, elem_ptr) ((long)((elem_ptr) - gvec_arr(v)))

/**
 * Thêm giá trị val vào sau phần tử cuối cùng trong v và tăng kích thước lên 1.
 * Nếu kích thước hiện tại bằng dung lượng thì mảng được cấp phát lại với kích
 * thước lớn hơn trước khi thêm val.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 * @param val Giá trị được thêm vào vec-tơ v.
 * @return Không trả về giá trị.
 */
#define gvec_append(v, val) \
  do { \
    arr_append((v)->arr, val); \
  } while (0)

/**
 * Xóa phần tử có chỉ số idx khỏi vec-tơ v. Nếu v->free_value != NULL
 * thì gọi hàm v->free_value(gvec_elem(v, i)) - Giải phóng bộ nhớ
 * được gắn với đối tượng được xóa.
 * Nếu idx là chỉ số không hợp lệ thì không có thay đổi gì, nếu ngược lại
 * thì các phần tử có chỉ số > idx được dịch sang trái 1 vị trí, và kích
 * thước vec-tơ được giảm đi 1 đơn vị.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 * @param idx Chỉ số phần tử được xóa.
 */
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

/**
 * Chủ động thiết lập dung lượng cho vec-tơ v. Nếu dung lượng
 * mới < kích thược hiện tại của vec-tơ thì không làm gì, nếu
 * ngược lại thì cấp phát lại mảng với dung lượng = cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 * @param cap Dung lượng mới.
 * @return Không trả về giá trị.
 */
#define gvec_set_capacity(v, cap) \
  do { \
    int _sz = arr_size((v)->arr); \
    if ((cap) < _sz) { \
      break; \
    } \
    arr_set_capacity((v)->arr, (cap)); \
  } while (0)

/**
 * Giải phóng bộ nhớ được cấp phát cho v và các vùng nhớ ngoài
 * được gắn với các phần tử của vec-tơ nếu có (v->free_value != NULL).
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 * @return Không trả về giá trị.
 */
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

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng vec-tơ
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới vec-tơ.
 * Trước tiên value.v được ép kiểu thành gvec_t, sau đó con trỏ gvec_t
 * được truyền cho gvec_free.
 * @return Hàm không trả về giá trị.
 */
void gvec_gtype_free(gtype value);

/**
 * Sắp xếp các phần tử của vec-tơ.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 * @param cmp Con trỏ tới hàm so sách các đối tượng ::gtype được lưu trong vec-tơ.
 * Đối số cmp có kiểu như hàm so sánh cho qsort (stdlib.h).
 * @return Không trả về giá trị.
 */
#define gvec_qsort(v, cmp) \
  qsort(ARR((v)->arr), gvec_size(v), sizeof(gtype), cmp)

/**
 * Duyệt tuần tự các phần tử của vec-tơ
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu gvec_t).
 * @param cur Con trỏ tới phần tự hiện tại của vec-tơ trong vòng lặp,
 * có kiểu ::gtype *.
 */
#define gvec_traverse(cur, v) \
  for (gtype *cur = gvec_arr(v), *end = gvec_arr(v) + gvec_size(v); cur < end; ++cur)

#endif  // GVEC_H_
