/* (C) Nguyen Ba Ngoc 2021 */

/** @file
 * @brief Khai báo giao diện vec-tơ của các giá trị \ref gtype.
 *
 * Có thể truy cập ngẫu nhiên đến 1 phần tử bất kỳ trong vec-tơ
 * theo chỉ số và sắp xếp nhanh vec-tơ tương tự như mảng.
 * Kích thước của vec-tơ có thể thay đổi sau khi được tạo
 * (dựa trên realloc) vì vậy linh động hơn mảng thông thường và
 * cũng có phạm vi ứng dụng rộng hơn.
 */

#ifndef CONT_VECTOR_H_
#define CONT_VECTOR_H_

#include "base/gtype.h"

struct vector;

/**
 * Trong vec-tơ size là số lượng phần tử mảng đã sử dụng,
 * còn capacity là số lượng phần tử đã được cấp phát cho
 * mảng cơ sở (elems), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Trả về kích thước (size) của vec-tơ, giá trị có kiểu long.
 * \memberof vector
 */
long vsize(const struct vector *v);

/**
 * Kiểm tra xem vec-tơ có rỗng không
 * 
 * @param v - Con trỏ tới vec-tơ.
 * @return 1 nếu vec-tơ rỗng, 0 nếu có phần tử.
 * \memberof vector
 */
int vempty(const struct vector *v);

/**
 * Trong vec-tơ size là số lượng phần tử mảng đã sử dụng,
 * còn capacity là số lượng phần tử đã được cấp phát cho
 * mảng cơ sở (arr), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Trả về dung lượng (capacity) của vec-tơ, giá trị có kiểu long.
 * \memberof vector
 */
long vcap(const struct vector *v);

/**
 * Hệ số tăng dung lượng của vec-tơ khi append
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *)
 * @return Trả về hệ số tăng dung lượng (k), có kiểu double.
 * \memberof vector
 */
double vratio(const struct vector *v);

/**
 * Con trỏ hàm giải phóng bộ nhớ động của phần tử
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *)
 * @return Trả về con trỏ hàm, có kiểu free_fn_t.
 * \memberof vector
 */
free_fn_t vfv(const struct vector *v);

/**
 * Thiết lập con trỏ hàm giải phóng bộ nhớ động của phần tử
 * 
 * @param v Con trỏ tới đối tượng vec-tơ
 * @param fv Con trỏ hàm giải phóng bộ nhớ
 * @return Chuyển tiếp con trỏ v
 * \memberof vector
 */
struct vector *vsetfv(struct vector *v, free_fn_t fv);

/**
 * Giao diện mảng của vec-tơ.
 * \code{.c}
 * varr(v)[0];  \\ Phần tử đầu tiên của vec-tơ v.
 * \endcode
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Trả về con trỏ tới phần tử đầu tiên của mảng (kiểu ::gtype *)
 * \memberof vector
 */
gtype *varr(struct vector *v);

/**
 * Chỉ định phần tử của vec-tơ bằng chỉ số.
 * \code{.c}
 *  vref(v, 0);  // Con trỏ tới phần tử đầu tiên của vec-tơ v.
 * \endcode
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param i Chỉ số của phần tử, là số nguyên và < #vsize(v).
 * @return Phần tử có chỉ số i trong vec-tơ v, 
 * kết quả là lvalue có kiểu ::gtype.
 * \memberof vector
 */
gtype *vref(struct vector *v, long i);

/**
 * Chỉ số của phần tử trong vec-tơ.
 * \code{.c}
 * vidx(vref(v, i)) == i;
 * \endcode
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param elem_ptr Con trỏ tới 1 phần tử hợp lệ trong vec-tơ.
 * @return Chỉ số của phần tử được trỏ tới bởi elem_ptr.
 * \memberof vector
 */
long vidx(struct vector *v, gtype *elem_ptr);

/**
 * Thay đổi dung lượng của vec-tơ, có thể tăng hoặc giảm
 * nhưng không giảm xuống < kích thước hiện có
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param newcap Dung lượng mới
 * @return Chuyển tiếp con trỏ v.
 * \memberof vector
 */
struct vector *vreserve(struct vector *v, long newcap);

/**
 * Thay đổi kích thước của vec-tơ, có thể tăng hoặc giảm.
 * Kéo theo thay đổi dung lượng nếu kích thước mới >
 * dung lượng hiện tại.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param newsz Kích thước mới
 * @return Chuyển tiếp con trỏ v
 * \memberof vector
 */
struct vector *vresize(struct vector *v, long newsz);

/**
 * Thêm giá trị val vào sau phần tử cuối cùng trong v và tăng kích thước lên 1.
 * Nếu vec-tơ đang đầy thì được tăng dung lượng trước khi thêm val.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param val Giá trị được thêm vào vec-tơ v.
 * @return Chuyển tiếp con trỏ v.
 * \memberof vector
 */
struct vector *_vappend(struct vector *v, gtype val);

#define vappend(v, elem) GCALL2(_vappend, v, elem)
static inline struct vector *_vappend_l(struct vector *v, long elem) {
  return _vappend(v, GLONG(elem));
}
static inline struct vector *_vappend_d(struct vector *v, double elem) {
  return _vappend(v, GDOUBLE(elem));
}
static inline struct vector *_vappend_s(struct vector *v, char *elem) {
  return _vappend(v, GSTR(elem));
}
static inline struct vector *_vappend_v(struct vector *v, char *elem) {
  return _vappend(v, GVOID(elem));
}

/**
 * Xóa phần tử có chỉ số idx khỏi vec-tơ v.
 * Nếu idx là chỉ số không hợp lệ thì không có thay đổi gì, nếu ngược lại
 * thì các phần tử có chỉ số > idx được dịch sang trái 1 vị trí, và kích
 * thước vec-tơ được giảm đi 1 đơn vị.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param idx Chỉ số phần tử được xóa.
 * @return Chuyển tiếp con trỏ v nếu thành công, hoặc NULL
 * nếu phát sinh lỗi.
 * \memberof vector
 */
struct vector *vremove(struct vector *v, long idx);

/**
 * Thêm 1 phần tử vào trước 1 phần tử đang có trong vec-tơ.
 * 
 * @param v - Con trỏ tới vec-tơ.
 * @param e - Phần tử được thêm vào.
 * @param i - Chỉ số phần tử được sử dụng làm chốt.
 * @return Chuyển tiếp vec-tơ v, hoặc trả về NULL nếu phát sinh lỗi.
 */
struct vector *vinsert_before(struct vector *v, gtype e, long i);

/**
 * Làm rỗng vec-tơ: Giải phóng các vùng nhớ được cấp phát cho mảng
 * và các phần tử của v. Sau đó thiết lập lại kích thước vec-tơ = 0,
 * dung lượng vec-tơ không thay đổi.
 *
 * @param v Con trỏ tới đối tượng kiểu vec-tơ
 * @return Chuyển tiếp con trỏ v.
 *
 * Tham khảo: vresize(v, cap) - Thay đổi kích thước vec-tơ
 * \memberof vector
 */
struct vector *vclear(struct vector *v);

/**
 * Giải phóng bộ nhớ được cấp phát cho v và các vùng nhớ ngoài
 * được gắn với các phần tử của vec-tơ nếu có (v->fv != NULL).
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Không trả về giá trị.
 * \memberof vector
 */
void vfree(struct vector *v);

/**
 * Gán tất cả các phần tử của vec-tơ = value
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param value Giá trị khởi tạo.
 * @return Không trả về giá trị.
 * \memberof vector
 */
void vfill(struct vector *v, gtype value);

/**
 * Hỗ trợ sử dụng vec-tơ như ngăn xếp - xếp phần tử
 * vào ngăn xếp.
 * 
 * @param v - Con trỏ tới đối tượng vec-tơ.
 * @param val - Phần tử cần thêm vào.
 * @return Con trỏ v - hỗ trợ chuỗi gọi hàm.
 * \memberof vector
 */
struct vector *vpush(struct vector *v, gtype val);

/**
 * Hỗ trợ sử dụng vec-tơ như ngăn xếp - xóa phần tử 
 * khỏi ngăn xếp.
 * 
 * @param v - Con trỏ tới đối tượng vec-tơ.
 * @return Con trỏ v - hỗ trợ chuỗi gọi hàm.
 * \memberof vector
 */
struct vector *vpop(struct vector *v);

/*** Giao diện ngăn xếp ***/

/**
 * Đọc đỉnh của ngăn xếp.
 * 
 * @param v - Con trỏ tới đối tượng vec-tơ.
 * @return Trả về con trỏ tới đỉnh ngăn xếp nếu tồn tại, 
 * hoặc NULL nếu không tồn tại.
 * \memberof vector
 */
gtype *vtop(struct vector *v);

/**
 * Hàm tạo đối tượng vec-tơ với kích thước ban đầu = sz.
 * Dùng cho các phần tử có kiểu vô hướng (kiểu long, double, v.v..),
 * phần tử không sử dụng bộ nhớ động. 
 * Con trỏ fv (hàm giải phóng bộ nhớ của phần tử) được khởi tạo = NULL.
 *
 * @param sz Số lượng phần tử cần cấp phát.
 * @return Trả về đối tượng tạo được nếu thành công hoặc NULL nếu thất bại.
 * \memberof vector
 */
struct vector *vcreate(long sz);

/**
 * Hàm tạo bản sao đầy đủ của vec-tơ
 *
 * @param v Con trỏ vec-tơ
 * @return Con trỏ tới bản sao đầy đủ của vec-tơ, kiểu ::struct vector *
 * \memberof vector
 */
struct vector *vclone(struct vector *v);

/**
 * Hàm kiểm tra 2 vec-tơ giống hệt nhau
 *
 * @param v1 Con trỏ vec-tơ thứ nhất
 * @param v2 Con trỏ vec-tơ thứ 2
 * @return 1 nếu giống nhau, 0 nếu ngược lại
 * \memberof vector
 */
int vsameas(struct vector *v1, struct vector *v2);

/**
 * Duyệt tuần tự các phần tử của vec-tơ theo chiều thuận
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param cur Con trỏ tới phần tự hiện tại của vec-tơ trong vòng lặp,
 * có kiểu \ref gtype *.
 */
#define VTRAVERSE(cur, v) \
  for (gtype *cur = varr(v), *end = varr(v) + vsize(v); \
    cur < end; ++cur)

/**
 * Duyệt tuần tự các phần tử của vec-tơ theo chiều ngược
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param cur Con trỏ tới phần tự hiện tại của vec-tơ trong vòng lặp,
 * có kiểu \ref gtype *.
 */
#define VRTRAVERSE(cur, v) \
  for (gtype *beg = varr(v), *cur = varr(v) + vsize(v) -1; \
    cur >= beg; --cur)

/**
 * Sắp xếp các phần tử của vec-tơ sử dụng stdlib.h qsort.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param cmp Con trỏ tới hàm so sách các đối tượng ::gtype được lưu trong vec-tơ.
 * Đối số cmp có kiểu như hàm so sánh cho qsort (stdlib.h).
 * Có nguyên mẫu là int (*)(const void *, const void *);
 */
#define VSORT(v, cmp) \
  qsort(varr(v), vsize(v), sizeof(gtype), cmp)

#endif  // CONT__VECTOR_H_
