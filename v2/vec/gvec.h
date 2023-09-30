#ifndef VEC_GVEC_H_
#define VEC_GVEC_H_

/* (C) Nguyen Ba Ngoc 2021 */

/** @file
 * @brief Vec-tơ của các giá trị ::gtype.
 *
 * Có thể truy cập ngẫu nhiên đến 1 phần tử bất kỳ trong vec-tơ
 * theo chỉ số và sắp xếp nhanh vec-tơ tương tự như mảng.
 * Kích thước của vec-tơ có thể thay đổi sau khi được tạo
 * (dựa trên realloc) vì vậy linh động hơn mảng thông thường và
 * cũng có phạm vi ứng dụng rộng hơn.
 */

#include "base/gtype.h"

/**
 * \headerfile "all.h"
 * Cấu trúc biểu diễn vec-tơ của các giá trị ::gtype.
 *
 * Các macros điều khiển (v phải có kiểu con trỏ ::struct gvector *):
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
 *   #gvec_reserve(v, cap) - Chủ động thiết lập dung lượng cho v.
 *
 *   #gvec_free(v) - Giải phóng bộ nhớ được cấp phát cho v.
 *
 *   #gvec_clear(v) - Làm rỗng v
 *
 *   #gvec_qsort(v, cmp) - Sắp xếp các phần tử của v bằng qsort với hàm so sánh cmp.
 *
 *   #gvec_traverse(cur, v) - Duyệt các phần tử của v theo chiều thuận.
 */
struct gvector {
  /**
   * Mảng cơ sở lưu các đối tượng ::gtype
   */
  gtype *elems;

  /**
   * Kích thước: Số lượng phần tử đang có trong vec-tơ
   */
  long sz;

  /**
   * Dung lượng: Số lượng phần tử đã được cấp phát
   */
  long cap;

  /**
   * Con trỏ tới hàm giải phóng dữ liệu được quản lý qua đối tượng
   * ::gtype trong mảng. Nếu != NULL thì hàm được gọi khi giải phóng
   * bộ nhớ của vec-tơ, nếu ngược lại (== NULL) thì các gọi hàm được
   * bỏ qua.
   */

  /**
   * Tốc độ tăng dung lượng khi append (> 1, mặc định = 2):
   *   dung lượng mới = dung lượng cũ * scale
   */
  double scale;

  /**
   * Con trỏ hàm giải phóng bộ nhớ động của các phần tử.
   */
  gtype_free_t free_value;
};

/**
 * Hàm tạo đối tượng vec-tơ, khởi tạo các phần tử = 0.
 *
 * @param n Kích thước & dung lượng ban đầu của vec-tơ.
 * @param free_value con trỏ hàm giải phóng bộ nhớ bên ngoài được gắn
 * với đối tượng ::gtype. Sử dụng NULL nếu không có bộ nhớ bên ngoài.
 * @return Trả về đối tượng tạo được nếu thành công hoặc NULL nếu thất bại.
 * \memberof gvector
 */
struct gvector *gvec_create(long n, gtype_free_t free_value);

/**
 * Hàm tạo đối tượng vec-tơ ở dạng đầy đủ, khởi tạo các phần tử với tham số value.
 *
 * @param size Kích thước ban đầu của vec-tơ.
 * @param cap Dung lượng ban đầu của vec-tơ, phía gọi cần đảm bảo size <= cap.
 * @param value Giá trị ban đầu để khởi tạo các phần tử.
 * @param free_value con trỏ hàm giải phóng bộ nhớ bên ngoài được gắn
 * với đối tượng ::gtype. Sử dụng NULL nếu không có bộ nhớ bên ngoài.
 * @return Trả về đối tượng tạo được nếu thành công hoặc NULL nếu thất bại.
 * \memberof gvector
 */
struct gvector *gvec_create_full(long size, long cap, gtype value,
        gtype_free_t free_value);

/**
 * Hàm tạo bản sao đầy đủ của vec-tơ
 *
 * @param v Con trỏ vec-tơ
 * @return Con trỏ tới bản sao đầy đủ của vec-tơ, kiểu ::struct gvector *
 */
struct gvector *gvec_clone(struct gvector *v);

/**
 * Hàm kiểm tra 2 vec-tơ giống hệt nhau
 *
 * @param v1 Con trỏ vec-tơ thứ nhất
 * @param v2 Con trỏ vec-tơ thứ 2
 * @return 1 nếu giống nhau, 0 nếu ngược lại
 */
int gvec_identical(struct gvector *v1, struct gvector *v2);

/**
 * Trong vec-tơ size là số lượng phần tử mảng đã sử dụng,
 * còn capacity là số lượng phần tử đã được cấp phát cho
 * mảng cơ sở (elems), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @return Trả về kích thước (size) của vec-tơ, giá trị có kiểu long.
 */
#define gvec_size(v) ((v)->sz)

/**
 * Trong vec-tơ size là số lượng phần tử mảng đã sử dụng,
 * còn capacity là số lượng phần tử đã được cấp phát cho
 * mảng cơ sở (arr), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @return Trả về dung lượng (capacity) của vec-tơ, giá trị có kiểu long.
 */
#define gvec_capacity(v) ((v)->cap)

/**
 * Tỉ lệ tăng dung lượng của vec-tơ khi append
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *)
 * @return Trả về tỉ lệ tăng dung lượng (scale), có kiểu double.
 */
#define gvec_scale(v) ((v)->scale)

/**
 * Giao diện mảng của vec-tơ.
 * \code{.c}
 * gvec_arr(v)[0];  \\ Phần tử đầu tiên của vec-tơ v.
 * \endcode
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @return Trả về con trỏ tới phần tử đầu tiên của mảng (kiểu ::gtype *)
 */
#define gvec_arr(v) ((v)->elems)

/**
 * Chỉ định phần tử của vec-tơ bằng chỉ số.
 * \code{.c}
 *  gvec_elem(v, 0);  \\ Phần tử đầu tiên của vec-tơ v.
 * \endcode
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param i Chỉ số của phần tử, là số nguyên và < #gvec_size(v).
 * @return Phần tử có chỉ số i trong vec-tơ v, kết quả là lvalue có kiểu ::gtype.
 */
#define gvec_elem(v, i) (gvec_arr(v)[(i)])

/**
 * Chỉ số của phần tử trong vec-tơ.
 * \code{.c}
 * gvec_idx_of(&gvec_elem(v, i)) == i;
 * \endcode
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param elem_ptr Con trỏ tới 1 phần tử hợp lệ trong vec-tơ.
 * @return Chỉ số của phần tử được trỏ tới bởi elem_ptr.
 */
#define gvec_idx_of(v, elem_ptr) ((long)((elem_ptr) - gvec_arr(v)))

/**
 * Thay đổi dung lượng của vec-tơ, có thể tăng hoặc giảm
 * nhưng không giảm xuống < kích thước hiện có
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param newcap Dung lượng mới
 * @return Không trả về kết quả
 */
#define gvec_reserve(v, newcap) \
  do { \
    if ((newcap) < gvec_size(v)) { \
      break; \
    } \
    (v)->elems = realloc((v)->elems, newcap * sizeof(gtype)); \
    (v)->cap = newcap; \
  } while (0)

/**
 * Thay đổi kích thước của vec-tơ, có thể tăng hoặc giảm.
 * Kéo theo thay đổi dung lượng nếu kích thước mới >
 * dung lượng hiện tại.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param newsz Kích thước mới
 * @return Không trả về kết quả
 */
#define gvec_resize(v, newsz) \
  do {\
    if (newsz > gvec_capacity(v)) { \
      gvec_reserve(v, newsz); \
    } else if (newsz < gvec_size(v) && (v)->free_value) { \
      for (long _j = newsz; _j < gvec_size(v); ++_j) { \
        (v)->free_value(gvec_elem(v, _j)); \
      }\
    }\
    gvec_size(v) = (newsz); \
  } while (0)

/**
 * Thêm giá trị val vào sau phần tử cuối cùng trong v và tăng kích thước lên 1.
 * Nếu vec-tơ đang đầy thì được tăng dung lượng trước khi thêm val.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param val Giá trị được thêm vào vec-tơ v.
 * @return Không trả về giá trị.
 */
#define gvec_append(v, val) \
  do { \
    if (gvec_size(v) == 0) { \
      gvec_reserve(v, 10); \
    } else if (gvec_size(v) == gvec_capacity(v)) {\
      gvec_reserve(v, gvec_scale(v) * gvec_size(v)); \
    } \
    gvec_elem(v, gvec_size(v)) = val; \
    gvec_resize(v, gvec_size(v) + 1); \
  } while (0)

/**
 * Thêm giá trị vào vị trí theo chỉ số, có thể mở rộng vec-tơ nếu cần
 *
 * @param i Chỉ số
 * @param v Con trỏ tới vec-tơ, có kiểu ::struct gvector*
 * @param e Phần tử được đưa vào
 * @return Không trả về giá trị
 */
#define gvec_force_set(v, i, e) \
  do { \
    if ((i) >= gvec_size(v)) { \
      gvec_resize((v), (i) + 1); \
    } \
    gvec_elem(v, i) = e; \
  } while (0)

/**
 * Xóa phần tử có chỉ số idx khỏi vec-tơ v. Nếu v->free_value != NULL
 * thì gọi hàm v->free_value(gvec_elem(v, i)) - Giải phóng bộ nhớ
 * được gắn với đối tượng được xóa.
 * Nếu idx là chỉ số không hợp lệ thì không có thay đổi gì, nếu ngược lại
 * thì các phần tử có chỉ số > idx được dịch sang trái 1 vị trí, và kích
 * thước vec-tơ được giảm đi 1 đơn vị.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param idx Chỉ số phần tử được xóa.
 */
#define gvec_remove(v, idx) \
  do { \
    gtype *_arr = gvec_arr(v); \
    long _sz = gvec_size(v); \
    if ((idx) >= _sz || (idx) < 0) { \
      break; \
    } \
    gtype _tmp = _arr[(idx)]; \
    for (long _i = (idx); _i < _sz - 1; ++_i) { \
      _arr[_i] = _arr[_i + 1]; \
    } \
    _arr[_sz - 1] = _tmp; \
    gvec_resize(v, _sz - 1); \
  } while (0)

/**
 * Duyệt tuần tự các phần tử của vec-tơ
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param cur Con trỏ tới phần tự hiện tại của vec-tơ trong vòng lặp,
 * có kiểu ::gtype *.
 */
#define gvec_traverse(cur, v) \
  for (gtype *cur = gvec_arr(v), *end = gvec_arr(v) + gvec_size(v); cur < end; ++cur)

/**
 * Làm rỗng vec-tơ: Giải phóng các vùng nhớ được cấp phát cho mảng
 * và các phần tử của v. Sau đó thiết lập lại kích thước vec-tơ = 0,
 * dung lượng vec-tơ không thay đổi.
 *
 * @param v Con trỏ tới đối tượng kiểu vec-tơ
 * @return Không trả về giá trị
 *
 * Tham khảo: #gvec_reserve(v, cap) - Thay đổi dung lượng
 */
#define gvec_clear(v) \
  gvec_resize(v, 0); \

/**
 * Giải phóng bộ nhớ được cấp phát cho v và các vùng nhớ ngoài
 * được gắn với các phần tử của vec-tơ nếu có (v->free_value != NULL).
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @return Không trả về giá trị.
 */
#define gvec_free(v) \
  do{ \
    gvec_clear(v); \
    free((v)->elems); \
    free(v); \
  } while (0)

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng vec-tơ
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới vec-tơ.
 * Trước tiên value.v được ép kiểu thành struct gvector *,
 * sau đó con trỏ struct gvector * được truyền cho gvec_free.
 * @return Hàm không trả về giá trị.
 */
void gtype_free_gvec(gtype value);

/**
 * Sắp xếp các phần tử của vec-tơ sử dụng stdlib.h qsort.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param cmp Con trỏ tới hàm so sách các đối tượng ::gtype được lưu trong vec-tơ.
 * Đối số cmp có kiểu như hàm so sánh cho qsort (stdlib.h).
 * Có nguyên mẫu là int (*)(const void *, const void *);
 * @return Không trả về giá trị.
 */
#define gvec_qsort(v, cmp) \
  qsort(gvec_arr(v), gvec_size(v), sizeof(gtype), cmp)

/**
 * Sắp xếp các phần tử của vec-tơ sử dụng quicksort (tự phát triển).
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param cmp Con trỏ tới hàm so sách các đối tượng ::gtype được lưu trong vec-tơ.
 * Có nguyên mẫu là int (*)(gtype, gtype), có kiểu là ::gtype_cmp_t.
 * @return Không trả về giá trị.
 */
#define gvec_quicksort(v, cmp) \
  quicksort(gvec_size(v), gvec_arr(v), cmp)

/**
 * Sắp xếp các phần tử của vec-tơ bằng giải thuật sắp xếp chọn.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param cmp Con trỏ tới hàm so sách các đối tượng ::gtype được lưu trong vec-tơ.
 * Đối số cmp có kiểu gtype_cmp_t.
 * @return Không trả về giá trị.
 */
#define gvec_selsort(v, cmp) \
  selsort(gvec_size(v), gvec_arr(v), cmp)

/**
 * Sắp xếp các phần tử của vec-tơ bằng giải thuật sắp xếp chèn.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param cmp Con trỏ tới hàm so sách các đối tượng ::gtype được lưu trong vec-tơ.
 * Đối số cmp có kiểu gtype_cmp_t.
 * @return Không trả về giá trị.
 */
#define gvec_insort(v, cmp) \
  insort(gvec_size(v), gvec_arr(v), cmp)

/**
 * Sắp xếp các phần tử của vec-tơ bằng giải thuật sắp xếp nổi bọt.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct gvector *).
 * @param cmp Con trỏ tới hàm so sách các đối tượng ::gtype được lưu trong vec-tơ.
 * Đối số cmp có kiểu gtype_cmp_t.
 * @return Không trả về giá trị.
 */
#define gvec_bubsort(v, cmp) \
  bubsort(gvec_size(v), gvec_arr(v), cmp);

/**
 * Xuất các phần tử của vec-tơ
 *
 * @param v Con trỏ tới đối tượng vec-tơ
 * @param pp Hàm xuất giá trị gtype
 */
void gvec_pprint(struct gvector *v, gtype_print_t pp);

/**
 * Sinh ngẫu nhiên 1 vec-tơ chứa giá trị kiểu long
 *
 * @param n Số lượng phần tử
 * @return Con trỏ tới vec-tơ được tạo, có kiểu ::struct gvector *
 */
struct gvector *gvec_rand_l(long n);

#define gvec_fill(v, value) \
  do { \
    gvec_traverse(_cur, v) { \
      *_cur = (value); \
    } \
  } while (0)

#endif  // VEC_GVEC_H_
