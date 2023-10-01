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

#ifdef CGEN_DEBUG
#include "base/flog.h"
#endif  // CGEN_DEBUG

#include "base/gtype.h"

/**
 * \headerfile "vector.h"
 * Cấu trúc biểu diễn vec-tơ của các giá trị ::gtype.
 *
 * Các macros điều khiển (v phải có kiểu con trỏ ::struct vector *):
 *
 *   #vcreate(...) - Lựa chọn hàm tạo theo số lượng tham số.
 * 
 *   #vsize(v) - Kích thước của v.
 *
 *   #vcap(v) - Dung lượng của v.
 *
 *   #varr(v) - Mảng các phần tử của v.
 *
 *   #vref(v, i) - Con trỏ tới phần tử thứ i của v.
 *
 *   #vidx(v, eptr) - Chỉ số của phần tử trong v được trỏ tới bởi eptr.
 * 
 *   #vfreeval(v) - Con trỏ hàm giải phóng bộ nhớ động của v.
 *
 *   #vappend(v, val) - Thêm val vào sau phần tử cuối cùng trong v.
 *
 *   #vremove(v, idx) - Xóa phần tử có chỉ số idx khỏi v.
 *
 *   #vreserve(v, cap) - Chủ động thiết lập dung lượng cho v.
 *
 *   #vfree(v) - Giải phóng bộ nhớ được cấp phát cho v.
 *
 *   #vclear(v) - Làm rỗng v
 *
 *   #vsort(v, cmp) - Sắp xếp các phần tử của v bằng qsort với hàm so sánh cmp.
 *
 *   #vtraverse(cur, v) - Duyệt các phần tử của v theo chiều thuận.
 * 
 *   #vrtraverse(cur, v) - Duyệt các phần tử của v theo chiều ngược.
 * 
 *   #vfill(v, value) - Gán các phần tử của v = value.
 */
struct vector {
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
   *   dung lượng mới = dung lượng cũ * k
   */
  double k;

  /**
   * Con trỏ hàm giải phóng bộ nhớ động của các phần tử.
   */
  gtype_free_t fv;
};

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
 * Trong vec-tơ size là số lượng phần tử mảng đã sử dụng,
 * còn capacity là số lượng phần tử đã được cấp phát cho
 * mảng cơ sở (elems), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Trả về kích thước (size) của vec-tơ, giá trị có kiểu long.
 */
#define vsize(v) (0 + (v)->sz)

/**
 * Trong vec-tơ size là số lượng phần tử mảng đã sử dụng,
 * còn capacity là số lượng phần tử đã được cấp phát cho
 * mảng cơ sở (arr), size luôn luôn <= cap.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Trả về dung lượng (capacity) của vec-tơ, giá trị có kiểu long.
 */
#define vcap(v) (0 + (v)->cap)

/**
 * Hệ số tăng dung lượng của vec-tơ khi append
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *)
 * @return Trả về hệ số tăng dung lượng (k), có kiểu double.
 */
#define vratio(v) (0 + (v)->k)

/**
 * Con trỏ hàm giải phóng bộ nhớ động của phần tử
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *)
 * @return Trả về con trỏ hàm, có kiểu gtype_free_t.
 */
#define vfreeval(v) ((gtype_free_t)(v)->fv)

/**
 * Giao diện mảng của vec-tơ.
 * \code{.c}
 * varr(v)[0];  \\ Phần tử đầu tiên của vec-tơ v.
 * \endcode
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Trả về con trỏ tới phần tử đầu tiên của mảng (kiểu ::gtype *)
 */
#define varr(v) ((v)->elems)

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
#define vref(v, i) (varr(v) + (i))

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
#define vidx(v, elem_ptr) ((long)((elem_ptr) - varr(v)))

/**
 * Thay đổi dung lượng của vec-tơ, có thể tăng hoặc giảm
 * nhưng không giảm xuống < kích thước hiện có
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param newcap Dung lượng mới
 * @return Không trả về kết quả
 */
#define vreserve(v, newcap) \
  do { \
    if ((newcap) < vsize(v)) { \
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
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param newsz Kích thước mới
 * @return Không trả về kết quả
 */
#define vresize(v, newsz) \
  do {\
    if (newsz > vcap(v)) { \
      vreserve(v, newsz); \
    } else if (newsz < vsize(v) && (v)->fv) { \
      for (long _j = newsz; _j < vsize(v); ++_j) { \
        (v)->fv(vref(v, _j)); \
      }\
    }\
    v->sz = (newsz); \
  } while (0)

/**
 * Thêm giá trị val vào sau phần tử cuối cùng trong v và tăng kích thước lên 1.
 * Nếu vec-tơ đang đầy thì được tăng dung lượng trước khi thêm val.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param val Giá trị được thêm vào vec-tơ v.
 * @return Không trả về giá trị.
 */
#define vappend(v, val) \
  do { \
    if (vsize(v) == 0) { \
      vreserve(v, 10); \
    } else if (vsize(v) == vcap(v)) {\
      vreserve(v, vratio(v) * vsize(v)); \
    } \
    *(vref(v, vsize(v))) = val; \
    vresize(v, vsize(v) + 1); \
  } while (0)

/**
 * Thêm giá trị vào vị trí theo chỉ số, có thể mở rộng vec-tơ nếu cần
 *
 * @param i Chỉ số
 * @param v Con trỏ tới vec-tơ, có kiểu ::struct vector*
 * @param e Phần tử được đưa vào
 * @return Không trả về giá trị
 */
#define vfset(v, i, e) \
  do { \
    if ((i) >= vsize(v)) { \
      vresize((v), (i) + 1); \
    } \
    *(vref(v, i)) = e; \
  } while (0)

/**
 * Xóa phần tử có chỉ số idx khỏi vec-tơ v.
 * Nếu idx là chỉ số không hợp lệ thì không có thay đổi gì, nếu ngược lại
 * thì các phần tử có chỉ số > idx được dịch sang trái 1 vị trí, và kích
 * thước vec-tơ được giảm đi 1 đơn vị.
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param idx Chỉ số phần tử được xóa.
 */
#define vremove(v, idx) \
  do { \
    gtype *_arr = varr(v); \
    long _sz = vsize(v); \
    if ((idx) >= _sz || (idx) < 0) { \
      break; \
    } \
    gtype _tmp = _arr[(idx)]; \
    for (long _i = (idx); _i < _sz - 1; ++_i) { \
      _arr[_i] = _arr[_i + 1]; \
    } \
    _arr[_sz - 1] = _tmp; \
    vresize(v, _sz - 1); \
  } while (0)

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
 * Làm rỗng vec-tơ: Giải phóng các vùng nhớ được cấp phát cho mảng
 * và các phần tử của v. Sau đó thiết lập lại kích thước vec-tơ = 0,
 * dung lượng vec-tơ không thay đổi.
 *
 * @param v Con trỏ tới đối tượng kiểu vec-tơ
 * @return Không trả về giá trị
 *
 * Tham khảo: #vreserve(v, cap) - Thay đổi dung lượng
 */
#define vclear(v) \
  vresize(v, 0); \

/**
 * Giải phóng bộ nhớ được cấp phát cho v và các vùng nhớ ngoài
 * được gắn với các phần tử của vec-tơ nếu có (v->fv != NULL).
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @return Không trả về giá trị.
 */
#define vfree(v) \
  do{ \
    vclear(v); \
    free((v)->elems); \
    free(v); \
  } while (0)

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

/**
 * Gán tất cả các phần tử của vec-tơ = value
 *
 * @param v Con trỏ tới đối tượng vec-tơ (có kiểu struct vector *).
 * @param value Giá trị khởi tạo.
 * @return Không trả về giá trị.
 */
#define vfill(v, value) \
  do { \
    vtraverse(_cur, v) { \
      *_cur = (value); \
    } \
  } while (0)

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng vec-tơ
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới vec-tơ.
 * Trước tiên value.v được ép kiểu thành struct vector *,
 * sau đó con trỏ struct vector * được truyền cho vfree.
 * @return Hàm không trả về giá trị.
 */
static void gfree_vec(gtype *value) {
  vfree(value->vec);
}

/**
 * Xuất các phần tử của vec-tơ
 *
 * @param v Con trỏ tới đối tượng vec-tơ
 * @param pp Hàm xuất giá trị gtype
 */
static void vpprint(struct vector *v, gtype_print_t pp) {
  vtraverse(cur, v) {
    pp(cur);
  }
}

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
static struct vector *vcreate1(long n) {
  struct vector *v = malloc(sizeof(struct vector));
  v->fv = NULL;
  if (n < 0) {
#ifdef CGEN_DEBUG
    flog(ERROR, "Tạo vec-tơ với kích thước không hợp lệ, n = %ld", n);
#endif  // CGEN_DEBUG
    return NULL;
  }
  v->sz = n;
  v->cap = n > 0? n: 8;

  /* Mặc định x 2 dung lượng mỗi lần tăng kích thước*/
  v->k = 2.0;
  v->elems = calloc(v->cap, sizeof(gtype));
  return v;
}

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
static struct vector *vcreate2(long n, gtype_free_t fv) {
  struct vector *base = vcreate1(n);
  if (base) {
    base->fv = fv;
  }
  return base;
}

/**
 * Hàm tạo bản sao đầy đủ của vec-tơ
 *
 * @param v Con trỏ vec-tơ
 * @return Con trỏ tới bản sao đầy đủ của vec-tơ, kiểu ::struct vector *
 */
static struct vector *vclone(struct vector *v) {
  struct vector *v2 = malloc(sizeof(struct vector));
  memcpy(v2, v, sizeof(struct vector));
  if (v->cap == 0) {
    v2->elems = NULL;
    return v2;
  }
  size_t elems_size = v2->cap * sizeof(gtype);
  v2->elems = malloc(elems_size);
  memcpy(v2->elems, v->elems, elems_size);
  return v2;
}

/**
 * Hàm kiểm tra 2 vec-tơ giống hệt nhau
 *
 * @param v1 Con trỏ vec-tơ thứ nhất
 * @param v2 Con trỏ vec-tơ thứ 2
 * @return 1 nếu giống nhau, 0 nếu ngược lại
 */
static int vsameas(struct vector *v1, struct vector *v2) {
  if (v1->sz != v2->sz || v1->cap != v2->cap) {
    return 0;
  }
  size_t elems_size = v1->cap * sizeof(gtype);
  char *p = (char *)(v1->elems),
       *q = (char *)(v2->elems);
  for (size_t i = 0; i < elems_size; ++i) {
    if (p[i] != q[i]) {
      return 0;
    }
  }
  return 1;
}

#endif  // CONT_VECTOR_H_
