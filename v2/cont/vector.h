#ifndef CONT_VECTOR_H_
#define CONT_VECTOR_H_

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
 * Trong vec-tơ size là số lượng phần tử mảng đã sử dụng,
 * còn capacity là số lượng phần tử đã được cấp phát cho
 * mảng cơ sở (elems), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Trả về kích thước (size) của vec-tơ, giá trị có kiểu long.
 */
long vsize(const struct vector *v);

/**
 * Trong vec-tơ size là số lượng phần tử mảng đã sử dụng,
 * còn capacity là số lượng phần tử đã được cấp phát cho
 * mảng cơ sở (arr), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Trả về dung lượng (capacity) của vec-tơ, giá trị có kiểu long.
 */
long vcap(const struct vector *v);

/**
 * Hệ số tăng dung lượng của vec-tơ khi append
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *)
 * @return Trả về hệ số tăng dung lượng (k), có kiểu double.
 */
double vratio(const struct vector *v);

/**
 * Con trỏ hàm giải phóng bộ nhớ động của phần tử
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *)
 * @return Trả về con trỏ hàm, có kiểu gtype_free_t.
 */
gtype_free_t vfreeval(const struct vector *v);

/**
 * Giao diện mảng của vec-tơ.
 * \code{.c}
 * varr(v)[0];  \\ Phần tử đầu tiên của vec-tơ v.
 * \endcode
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Trả về con trỏ tới phần tử đầu tiên của mảng (kiểu ::gtype *)
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
 * @return Phần tử có chỉ số i trong vec-tơ v, kết quả là lvalue có kiểu ::gtype.
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
 */
long vidx(struct vector *v, gtype *elem_ptr);

/**
 * Thay đổi dung lượng của vec-tơ, có thể tăng hoặc giảm
 * nhưng không giảm xuống < kích thước hiện có
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param newcap Dung lượng mới
 * @return Không trả về kết quả
 */
void vreserve(struct vector *v, long newcap);

/**
 * Thay đổi kích thước của vec-tơ, có thể tăng hoặc giảm.
 * Kéo theo thay đổi dung lượng nếu kích thước mới >
 * dung lượng hiện tại.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param newsz Kích thước mới
 * @return Không trả về kết quả
 */
void vresize(struct vector *v, long newsz);

/**
 * Thêm giá trị val vào sau phần tử cuối cùng trong v và tăng kích thước lên 1.
 * Nếu vec-tơ đang đầy thì được tăng dung lượng trước khi thêm val.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param val Giá trị được thêm vào vec-tơ v.
 * @return Không trả về giá trị.
 */
void vappend(struct vector *v, gtype val);

/**
 * Xóa phần tử có chỉ số idx khỏi vec-tơ v.
 * Nếu idx là chỉ số không hợp lệ thì không có thay đổi gì, nếu ngược lại
 * thì các phần tử có chỉ số > idx được dịch sang trái 1 vị trí, và kích
 * thước vec-tơ được giảm đi 1 đơn vị.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param idx Chỉ số phần tử được xóa.
 */
void vremove(struct vector *v, long idx);

/**
 * Làm rỗng vec-tơ: Giải phóng các vùng nhớ được cấp phát cho mảng
 * và các phần tử của v. Sau đó thiết lập lại kích thước vec-tơ = 0,
 * dung lượng vec-tơ không thay đổi.
 *
 * @param v Con trỏ tới đối tượng kiểu vec-tơ
 * @return Không trả về giá trị
 *
 * Tham khảo: vresize(v, cap) - Thay đổi kích thước vec-tơ
 */
void vclear(struct vector *v);

/**
 * Giải phóng bộ nhớ được cấp phát cho v và các vùng nhớ ngoài
 * được gắn với các phần tử của vec-tơ nếu có (v->fv != NULL).
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Không trả về giá trị.
 */
void vfree(struct vector *v);

/**
 * Gán tất cả các phần tử của vec-tơ = value
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param value Giá trị khởi tạo.
 * @return Không trả về giá trị.
 */
void vfill(struct vector *v, gtype value);

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng vec-tơ
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới vec-tơ.
 * Trước tiên value.v được ép kiểu thành struct vector *,
 * sau đó con trỏ struct vector * được truyền cho vfree.
 * @return Hàm không trả về giá trị.
 */
void gfree_vec(gtype *value);

/**
 * Hàm tạo đối tượng vec-tơ với n phần tử.
 * Dùng cho các phần tử có kiểu vô hướng (kiểu long, double, v.v..),
 * phần tử không sử dụng bộ nhớ động. 
 * Con trỏ fv (hàm giải phóng bộ nhớ của phần tử) được khởi tạo = NULL.
 *
 * @param n Số lượng phần tử cần cấp phát.
 * @return Trả về đối tượng tạo được nếu thành công hoặc NULL nếu thất bại.
 * \memberof gvector
 */
struct vector *vcreate1(long n);

/**
 * Hàm tạo đối tượng vec-tơ với n phần tử.
 * Dùng cho các phần tử có kiểu con trỏ (char *, void *, v.v..),
 * phần tử có sử dụng bộ nhớ động. 
 *
 * @param n Số lượng phần tử cần cấp phát.
 * @param fv Con trỏ hàm giải phóng bộ nhớ động của các phần tử.
 * @return Trả về đối tượng tạo được nếu thành công hoặc NULL nếu thất bại.
 * \memberof gvector
 */
struct vector *vcreate2(long n, gtype_free_t fv);

/**
 * Hàm tạo bản sao đầy đủ của vec-tơ
 *
 * @param v Con trỏ vec-tơ
 * @return Con trỏ tới bản sao đầy đủ của vec-tơ, kiểu ::struct vector *
 */
struct vector *vclone(struct vector *v);

/**
 * Hàm kiểm tra 2 vec-tơ giống hệt nhau
 *
 * @param v1 Con trỏ vec-tơ thứ nhất
 * @param v2 Con trỏ vec-tơ thứ 2
 * @return 1 nếu giống nhau, 0 nếu ngược lại
 */
int vsameas(struct vector *v1, struct vector *v2);

#define select_creator(_1, _2, func, ...) func
/**
 * Macro điều hướng. Lệnh 1 tham số được điều hướng tới 
 * vcreate1, lệnh 2 tham số được điều hướng tới vcreate2.
 * 
 * * @return Trả về đối tượng tạo được nếu thành công hoặc NULL nếu thất bại.
 * \memberof gvector
 */
#define vcreate(...) \
    select_creator(__VA_ARGS__, vcreate2, vcreate1)(__VA_ARGS__)

/**
 * Duyệt tuần tự các phần tử của vec-tơ theo chiều thuận
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param cur Con trỏ tới phần tự hiện tại của vec-tơ trong vòng lặp,
 * có kiểu ::gtype *.
 */
#define vtraverse(cur, v) \
  for (gtype *cur = varr(v), *end = varr(v) + vsize(v); \
    cur < end; ++cur)

/**
 * Duyệt tuần tự các phần tử của vec-tơ theo chiều ngược
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param cur Con trỏ tới phần tự hiện tại của vec-tơ trong vòng lặp,
 * có kiểu ::gtype *.
 */
#define vrtraverse(cur, v) \
  for (gtype *beg = varr(v), *cur = varr(v) + vsize(v) -1; \
    cur >= beg; --cur)

/**
 * Sắp xếp các phần tử của vec-tơ sử dụng stdlib.h qsort.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param cmp Con trỏ tới hàm so sách các đối tượng ::gtype được lưu trong vec-tơ.
 * Đối số cmp có kiểu như hàm so sánh cho qsort (stdlib.h).
 * Có nguyên mẫu là int (*)(const void *, const void *);
 * @return Không trả về giá trị.
 */
#define vsort(v, cmp) \
  qsort(varr(v), vsize(v), sizeof(gtype), cmp)

#endif  // CONT__VECTOR_H_
