#ifndef CGEN_H_
#define CGEN_H_

/* (C) Nguyễn Bá Ngọc 2023 */

#define VERSION "2.0.0"

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define select_creator(_1, _2, func, ...) func

#define container_of(ptr, type, member) \
  ((type *)((void*)(ptr) - offsetof(type, member)))

#define New(TYPE, ...) TYPE ## _create(  __VA_ARGS__ )

#define Delete(TYPE, ptr) do        \
        {       \
          TYPE ## _free(ptr); \
          /*free(ptr);*/    \
        }       \
        while(0)

#define BENCH(NAME, ITER, ...)    do { \
        double _sum = 0, _start, _stop; \
        for (int _i = 0; _i < (ITER); ++_i) { \
          _start = clock(); \
          { __VA_ARGS__; } \
          _stop = clock(); \
          _sum += _stop - _start; \
        } \
        if ((ITER) > 1) { \
          printf("%s (trung bình %d lượt) = %.5g s\n", \
                (NAME), (ITER),  (_sum/CLOCKS_PER_SEC) / (ITER)); \
        } else { \
          printf("%s: %5g s\n", (NAME), _sum/CLOCKS_PER_SEC); \
        }\
    } while (0)

#define BENCH1_START() \
   long _bench1_start = clock()
#define BENCH1_END() \
   long _bench1_end = clock(); \
   printf("Time: %.3f\n", (double)(_bench1_end - _bench1_start)/CLOCKS_PER_SEC)

typedef union generic_type {
  long l;
  double d;
  char *s;
  void *v;
  union generic_type *g;
  struct gsllist *gsl;
  struct vector *vec;
  struct rbmtree *rbm;
} gtype;

#define gtype_zero (gtype_l(0l))

#define gtype_value(type, val) ((gtype){.type = (val)})
#define gtype_l(value) gtype_value(l, value)
#define gtype_d(value) gtype_value(d, value)
#define gtype_s(value) gtype_value(s, (char *)value)
#define gtype_v(value) gtype_value(v, value)
#define gtype_g(value) gtype_value(g, value)
#define gtype_gsl(value) gtype_value(gsl, value)
#define gtype_gvec(value) gtype_value(gvec, value)
#define gtype_rbm(value) gtype_value(rbm, value)

#define gtype_swap(v1, v2) \
  do { \
    gtype _tmp = (v1); \
    (v1) = (v2); \
    (v2) = _tmp; \
  } while (0)

typedef int (*gtype_cmp_t)(const gtype*, const gtype*);
typedef void (*gtype_free_t)(gtype*);
typedef int (*gtype_print_t)(const gtype*);

static inline int gtype_cmp_l(const gtype *v1, const gtype *v2) {
  return v1->l - v2->l;
}

static inline int gtype_rcmp_l(const gtype *v1, const gtype *v2) {
  return v2->l - v1->l;
}

static inline int gtype_cmp_d(const gtype *v1, const gtype *v2) {
  if (v1->d < v2->d) {
    return -1;
  } else if (v1->d > v2->d) {
    return 1;
  }
  return 0;
}

static inline int gtype_rcmp_d(const gtype *v1, const gtype *v2) {
  if (v2->d < v1->d) {
    return -1;
  } else if (v2->d > v1->d) {
    return 1;
  }
  return 0;
}

/**
 * Hàm so sánh các giá trị gtype chứa con trỏ chuỗi ký tự.
 *
 * @param v1 Đối số thứ nhất.
 * @param v2 Đỗ số thứ 2.
 * @return Giá trị trả về theo định dạng strcmp <br>
 *   -1 nếu v1.s < v2.s, <br>
 *    1 nếu ngược lại và v1.s > v2.s, <br>
 *    0 nếu ngược lại (v1.s == v2.s). <br>
 *
 * \memberof generic_type
 */
static inline int gtype_cmp_s(const gtype *v1, const gtype *v2) {
  return strcmp(v1->s, v2->s);
}

static inline int gtype_rcmp_s(const gtype *v1, const gtype *v2) {
  return strcmp(v2->s, v1->s);
}

static inline int gtype_qsort_l(const void *v1, const void *v2) {
  return ((const gtype*)v1)->l - ((const gtype*)v2)->l;
}

static inline int gtype_qsort_d(const void *v1, const void *v2) {
  if (((const gtype*)v1)->l > ((const gtype*)v2)->l) {
    return 1;
  } else if (((const gtype*)v1)->l < ((const gtype*)v2)->l) {
    return -1;
  }
  return 0;
}

static inline int gtype_qsort_s(const void *v1, const void *v2) {
  return strcmp(((const gtype*)v1)->s, ((const gtype*)v2)->s);
}

static int gtype_print_l(const gtype *value) {
  printf("%ld\n", value->l);
  return 0;  // Tương thích với foreach
}

static int gtype_print_d(const gtype *value) {
  printf("%f\n", value->d);
  return 0;
}

static int gtype_print_s(const gtype *value) {
  printf("%s\n", value->s);
  return 0;
}

/**
 * Giải phóng chuỗi được trỏ đến bởi con trỏ v.s
 *
 * @param v Giá trị gtype chứa con trỏ tới chuỗi.
 * @return Hàm không trả về giá trị.
 */
static void gtype_free_s(gtype v) {
  free(v.s);
}

static void gtype_free_v(gtype v) {
  free(v.v);
}

#define FLOG_VERSION "1.0.0";

#define flog(...) _flog(__FILE__, __LINE__, __VA_ARGS__)
static inline void _flog(const char *file, int line, const char *fmt, ...) {
  const char *filename = (strrchr(file, '/') ? strrchr(file, '/') + 1 : file);
  fprintf(stderr, "%s:%d: ", filename, line);

  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
  fprintf(stderr, "\n");
  fflush(stderr);
}

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
 * Hỗ trợ sử dụng vec-tơ như ngăn xếp - xếp phần tử
 * vào ngăn xếp.
 * 
 * @param v - Con trỏ tới đối tượng vec-tơ.
 * @param val - Phần tử cần thêm vào.
 * @return Con trỏ v - hỗ trợ chuỗi gọi hàm.
 */
struct vector *vpush(struct vector *v, gtype val);

/**
 * Hỗ trợ sử dụng vec-tơ như ngăn xếp - xóa phần tử 
 * khỏi ngăn xếp.
 * 
 * @param v - Con trỏ tới đối tượng vec-tơ.
 * @return Con trỏ v - hỗ trợ chuỗi gọi hàm.
 */
struct vector *vpop(struct vector *v);

/**
 * Hỗ trợ sử dụng vec-tơ như ngăn xếp - đọc phần tử
 * trên đỉnh ngăn xếp.
 * 
 * @param v - Con trỏ tới đối tượng vec-tơ.
 * @param out - Con trỏ tới đối tượng lưu giá trị đầu ra.
 * @return Con trỏ v - hỗ trợ chuỗi gọi hàm.
 */
struct vector *vtop(struct vector *v, gtype *out);

/**
 * Hàm tạo đối tượng vec-tơ với kích thước ban đầu = sz.
 * Dùng cho các phần tử có kiểu vô hướng (kiểu long, double, v.v..),
 * phần tử không sử dụng bộ nhớ động. 
 * Con trỏ fv (hàm giải phóng bộ nhớ của phần tử) được khởi tạo = NULL.
 *
 * @param sz Số lượng phần tử cần cấp phát.
 * @return Trả về đối tượng tạo được nếu thành công hoặc NULL nếu thất bại.
 * \memberof gvector
 */
struct vector *vcreate1(long sz);

/**
 * Hàm tạo đối tượng vec-tơ với sz phần tử.
 * Dùng cho các phần tử có kiểu con trỏ (char *, void *, v.v..),
 * phần tử có sử dụng bộ nhớ động. 
 *
 * @param sz Số lượng phần tử cần cấp phát.
 * @param fv Con trỏ hàm giải phóng bộ nhớ động của các phần tử.
 * @return Trả về đối tượng tạo được nếu thành công hoặc NULL nếu thất bại.
 * \memberof gvector
 */
struct vector *vcreate2(long sz, gtype_free_t fv);

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

#endif  // CGEN_H_