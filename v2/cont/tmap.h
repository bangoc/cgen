#ifndef CONT_TREEMAP_H_
#define CONT_TREEMAP_H_

/* (C) Nguyễn Bá Ngọc 2023 */
/**
 * @file
 * @brief Khai báo giao diện cấu trúc \ref tmap và \ref tnode
 * tương ứng.
 */

#include "base/core.h"

/******* Giao diện tnode ******/

struct tnode;
struct tmap;
/**
 * Truy cập con trỏ tới key của nút.
 * 
 * @param n - Con trỏ tới nút.
 * @return Con trỏ tới giá trị của nút.
 * \memberof tnode
 */
gtype *tkey_of(struct tnode *n);

/**
 * Truy cập con trỏ tới value của nút.
 * 
 * @param n - Con trỏ tới nút.
 * @return Con trỏ tới giá trị của nút.
 * \memberof tnode
 */
gtype *tvalue_of(struct tnode *n);

/**
 * Lấy phần tử trái nhất của 1 nút.
 * 
 * @param n - Con trỏ tới 1 nút.
 * @return Con trỏ tới nút trái nhất trong cây con
 * với gốc là n.
 * \memberof tnode
 */
struct tnode *tleft_most(struct tnode *n);

/**
 * Lấy phần tử phải nhất của 1 nút.
 * 
 * @param n - Con trỏ tới 1 nút.
 * @return Con trỏ tới nút phải nhất trong cây con
 * với gốc là n.
 * \memberof tnode
 */
struct tnode *tright_most(struct tnode *n);

/**
 * Lấy phần tử sâu nhất bên trái của 1 nút 
 * 
 * @param n - Con trỏ tới nút.
 * @return Con trỏ tới nút sâu nhất bên trái của n.
 * 
 * \memberof tnode
 */
struct tnode *tleft_deepest(struct tnode *n);

/** 
 * Tìm nút liền sau của x theo thứ tự trái-phải-nút
 * 
 * @param x - Con trỏ tới 1 nút của cây.
 * @return Trả về con trỏ tới nút liền sau nếu có,
 * hoặc NULL nếu không.
 * \memberof tnode
 */
struct tnode *tnext_lrn(struct tnode *x);

/**
 * Dịch chuyển sang cặp giá trị kế tiếp theo thứ tự 
 * trái-phải-nút.
 * 
 * @param pk - Con trỏ tới con trỏ tới khóa hiện tại.
 * @param pv - Con trỏ tới con trỏ tới giá trị hiện tại.
 * @return Không trả về giá trị.
 * \memberof tnode
 */
void tnextkv_lrn(gtype **pk, gtype **pv);

/** 
 * Tìm nút liền trước của x theo thứ tự trái-nút-phải
 * 
 * @param x - Con trỏ tới 1 nút của cây.
 * @return Trả về con trỏ tới nút liền trước nếu có,
 * hoặc NULL nếu không.
 * \memberof tnode
 */
struct tnode *tprev_lnr(struct tnode *x);

/**
 * Dịch chuyển sang cặp giá trị liền trước theo thứ tự 
 * trái-nút-phải.
 * 
 * @param pk - Con trỏ tới con trỏ tới khóa hiện tại.
 * @param pv - Con trỏ tới con trỏ tới giá trị hiện tại.
 * @return Không trả về giá trị.
 * \memberof tnode
 */
void tprevkv_lnr(gtype **pk, gtype **pv);

/** 
 * Tìm nút liền sau của x theo thứ tự trái-nút-phải
 * 
 * @param x - Con trỏ tới 1 nút của cây.
 * @return Trả về con trỏ tới nút liền sau nếu có,
 * hoặc NULL nếu không.
 * \memberof tnode
 */
struct tnode *tnext_lnr(struct tnode *x);

/**
 * Dịch chuyển cặp khóa và giá trị sang nút kế tiếp theo thứ tự
 * trái-nút-phải.
 * 
 * @param pk - Con trỏ tới con trỏ tới khóa hiện tại.
 * @param pv - Con trỏ tới con trỏ tới giá trị tương ứng.
 * @return Không trả về giá trị.
 * \memberof tnode
 */
void tnextkv_lnr(gtype **k, gtype **v);

/**
 * Kiểm tra 1 nút có phải nút đỏ hay không.
 * 
 * @param n - Con trỏ tới nút.
 * @return Trả về 1 nếu nút có mầu đỏ, hoặc 0 nếu không
 * phải nút đỏ.
 * 
 * \memberof tnode
 */
int tis_red(struct tnode *n);

/**
 * Kiểm tra 1 nút có phải nút đen hay không.
 * 
 * @param n - Con trỏ tới nút.
 * @return Trả về 1 nếu nút có mầu đen, hoặc 0 nếu không
 * phải nút đen.
 * 
 * \memberof tnode
 */
int tis_black(struct tnode *n);

/**
 * Truy cập con trái của 1 nút.
 * 
 * @param n - Con trỏ tới nút.
 * @return Con trỏ tới con trái của nút.
 * 
 * \memberof tnode
 */
struct tnode *tleft_of(struct tnode *n);

/**
 * Truy cập con phải của 1 nút.
 * 
 * @param n - Con trỏ tới nút.
 * @return Con trỏ tới con phải của nút.
 * 
 * \memberof tnode
 */
struct tnode *tright_of(struct tnode *n);

/**
 * Truy cập đỉnh của 1 nút.
 * 
 * @param n - Con trỏ tới nút.
 * @return Con trỏ tới đỉnh của nút.
 * 
 * \memberof tnode
 */
struct tnode *ttop_of(struct tnode *n);

/******* Giao diện tmap ******/
/**
 * Hàm tạo đối tượng điều khiển bảng cây.
 *
 * @param cmp Hàm so sánh các giá trị khóa, tham số bắt buộc,
 * phải != NULL.
 * @return Trả về con trỏ tới bảng cây nếu thành công, hoặc NULL
 * nếu không thể cấp phát bộ nhớ.
 *
 * \memberof tmap
 */
struct tmap *tcreate(compare_fnt cmp);

/**
 * Hàm tạo đối tượng điều khiển bảng cây với đầy đủ các tham số.
 *
 * @param cmp Con trỏ tới hàm so sánh các giá trị khóa, tham số bắt buộc,
 * phải != NULL.
 * @param fk Con trỏ tới hàm giải phóng bộ nhớ của khóa, thiết lập nếu
 * sử dụng con trỏ và cấp phát động. Có thể thiết lập = NULL.
 * @param fv Con trỏ tới hàm giải phóng bố nhớ của giá trị, thiết lập nếu
 * sử dụng con trỏ và cấp phát động. Có thể thiết lập = NULL;
 * @return Trả về con trỏ tới bảng cây nếu thành công, hoặc NULL
 * nếu không thể cấp phát bộ nhớ.
 *
 * \memberof tmap
 */
struct tmap *tconstruct(compare_fnt cmp, destructor_fnt fk, destructor_fnt fv);

/**
 * Thêm cặp (key, value) vào bảng t. Nếu key đã tồn tại thì
 * bỏ qua.
 *
 * @param t Con trỏ tới bảng cây.
 * @param key Khóa được thêm vào.
 * @param value Giá trị được thêm vào.
 * @return Trả về con trỏ tới value nếu đã tồn tại,
 * trả về NULL nếu chưa tồn tại hoặc phát sinh lỗi.
 *
 * \memberof tmap
 */
gtype *_tput(struct tmap *t, const gtype key, const gtype value);
#define tput(t, k, v) _tput(t, GTYPE(k), GTYPE(v))

/**
 * Truy cập giá trị được gắn với khóa
 * 
 * @param t - Con trỏ tới bảng.
 * @param key - Khóa.
 * @param value - Trả về con trỏ tới giá trị tương ứng,
 * hoặc NULL nếu khóa không có trong bảng.
 * 
 * \memberof tmap
 */
gtype *_tget(struct tmap *t, const gtype key);
#define tget(t, key) _tget(t, GTYPE(key))

/**
 * Thiết lập value là con trỏ tới giá trị tương ứng với key
 *
 * @param t - Con trỏ tới bảng.
 * @param k - Khóa.
 * @param v - Con trỏ đầu ra lưu giá trị.
 */
#define tbind(t, k_, v_) \
  _Generic((v_), \
    long *:   (v_) = (long*)tget(t, k_), \
    double *: (v_) = (double*)tget(t, k_), \
    char *:   (v_) = tget(t, k_)->s, \
    void *:   (v_) = tget(t, k_)->v, \
    default:  (v_) = tget(t, k_)->v \
  )

/**
 * Nếu key không có trong t thì bỏ qua, nếu ngược lại thì xóa cặp
 * khóa & giá trị tương ứng trong t, fk và fv được gọi nếu != NULL.
 *
 * @param t - Con trỏ tới bảng cây.
 * @param key - Khóa của cặp cần xóa.
 * @return Chuyển tiếp con trỏ t nếu thành công, hoặc NULL
 * nếu không xóa được (key không có trong bảng).
 *
 * \memberof tmap
 *
 */
struct tmap *_tremove(struct tmap *t, gtype key);
#define tremove(t, key) _tremove(t, GTYPE(key))

/**
 * Truy vấn kích thước (số lượng phần tử) của cây.
 * 
 * @param t - Con trỏ tới cây.
 * @return Số lượng phần tử của cây.
 * \memberof tmap
 */
long tsize(const struct tmap *t);

/**
 * Truy cập gốc của cây
 * 
 * @param t - Con trỏ tới cây.
 * @return Trả về con trỏ tới gốc của cây.
 * \memberof tmap
 */
struct tnode *troot(struct tmap *t);

/**
 * Truy cập thành viên fk của tmap.
 * 
 * @param t - Con trỏ tới bảng cây.
 * @return Trả về con trỏ hàm fk.
 */
destructor_fnt tfk(struct tmap *t);

/**
 * Truy cập thành viên fv của tmap.
 * 
 * @param t - Con trỏ tới bảng cây.
 * @return Trả về con trỏ hàm fv.
 */
destructor_fnt tfv(struct tmap *t);

/**
 * Thiết lập thành viên fk của tmap.
 * 
 * @param t - Con trỏ tới bảng cây.
 * @param fk - Con trỏ tới hàm giải phóng bộ nhớ của khóa.
 * @return Chuyển tiếp con trỏ t, hoặc trả về NULL nếu phát
 * sinh lỗi.
 */
struct tmap *tsetfk(struct tmap *t, destructor_fnt fk);

/**
 * Thiết lập thành viên fv của tmap.
 * 
 * @param t - Con trỏ tới bảng cây.
 * @param fv - Con trỏ tới hàm giải phóng bộ nhớ của khóa.
 * @return Chuyển tiếp con trỏ t, hoặc trả về NULL nếu phát
 * sinh lỗi.
 */
struct tmap *tsetfv(struct tmap *t, destructor_fnt fv);

/**
 * Giải phóng bộ nhớ của bảng cây.
 * 
 * @param op - Con trỏ tới bảng cây.
 * @return Không trả về giá trị.
 */
void tfree(void *op);

/**
 * Duyệt tuần tự các cặp khóa & giá trị trong bảng t theo thứ tự
 * trái-nút-phải. Các tham số k và v là các định danh do 
 * người sử dụng tự đặt và sẽ có kiểu \ref gtype *
 *
 * @param k Định danh sẽ được sử dụng như con trỏ tới khóa hiện hành.
 * @param v Định danh sẽ được sử dụng như con trỏ tới giá trị hiện hành.
 * @param t Con trỏ tới bảng cây.
 *
 */
#define TTRAVERSE_LNR(k, v, t) \
  for (gtype *k = (gtype*)tleft_most(troot(t)), \
             *v = k? tvalue_of((struct tnode*)k): NULL; \
       k != NULL && v != NULL; tnextkv_lnr(&k, &v))

/**
 * Mặc định là thứ tự tăng dần, tương đương với
 * #TTRAVERSE_LNR
 */
#define TTRAVERSE(k, v, t) TTRAVERSE_LNR(k, v, t)

/**
 * Duyệt tuần tự các cặp khóa & giá trị trong bảng t theo thứ tự
 * phải-nút-trái. Các tham số k và v là các định danh do 
 * người sử dụng tự đặt và sẽ có kiểu \ref gtype *
 *
 * @param k Định danh sẽ được sử dụng như con trỏ tới khóa hiện hành.
 * @param v Định danh sẽ được sử dụng như con trỏ tới giá trị hiện hành.
 * @param t Con trỏ tới bảng cây.
 *
 */
#define TTRAVERSE_RNL(k, v, t) \
  for (gtype *k = (gtype*)tright_most(troot(t)), \
             *v = k? tvalue_of((struct tnode*)k): NULL; \
       k != NULL && v != NULL; tprevkv_lnr(&k, &v))

/**
 * Mặc định là thứ tự giảm dần, tương đương với
 * #TTRAVERSE_RNL
 */
#define TRTRAVERSE(k, v, t) TTRAVERSE_RNL(k, v, t)

/**
 * Duyệt cây t theo thứ tự trái-phải-nút. Các tham số k và v
 * là các định danh do người sử dụng tự đặt và sẽ có kiểu 
 * \ref gtype *
 *
 * @param k Định danh sẽ được sử dụng như con trỏ tới khóa hiện hành.
 * @param v Định danh sẽ được sử dụng như con trỏ tới giá trị hiện hành.
 * @param t Con trỏ tới bảng cây.
 *
 */
#define TTRAVERSE_LRN(k, v, t) \
  for (gtype *k = (gtype*)tleft_deepest(troot(t)), \
             *v = k? tvalue_of((struct tnode *)k): NULL; \
       k != NULL; tnextkv_lrn(&k, &v))

#endif  // CONT_TREEMAP_H_