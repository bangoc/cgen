#ifndef CONT_TREEMAP_H_
#define CONT_TREEMAP_H_

/* (C) Nguyễn Bá Ngọc 2023 */
/**
 * @file
 * @brief Khai báo giao diện cấu trúc \ref tmap
 */

/**
 * Hàm tạo đối tượng điều khiển bảng cây.
 *
 * @param cmp Hàm so sánh các giá trị khóa, phải != NULL.
 * Tham khảo: gstr_cmp(gtype v1, gtype v2).
 * @param free_key Con trỏ tới hàm giải phóng bộ nhớ ngoài được gắn với khóa, tham khảo.
 * gtype_free_s(gtype v). Được gọi khi xóa dữ liệu nếu != NULL. Trong trường hợp không
 * có bộ nhớ ngoài hoặc không cần xóa bộ nhớ ngoài (như tình huống đang chia sẻ bộ nhớ
 * với 1 câu trúc lưu trữ khác) thì để = NULL.
 * @param free_value Con trỏ tới hàm giải phóng bộ nhớ ngoài được gắn với giá trị, tương
 * tự free_key.
 * @return Trả về con trỏ tới bảng cây nếu thành công, hoặc NULL
 * nếu không thể cấp phát bộ nhớ.
 *
 * \memberof tmap
 */
struct tmap *tcreate(gtype_cmp_t cmp);

/**
 * Thêm cặp (key, value) vào bảng t. Nếu key đã tồn tại thì
 * bỏ qua.
 *
 * @param t Con trỏ tới bảng cây.
 * @param key Khóa được thêm vào.
 * @param value Giá trị được thêm vào.
 * @return Trả về đối tượng trả về con trỏ tới value nếu đã tồn tại,
 * hoặc NULL nếu chưa tồn tại hoặc phát sinh lỗi.
 *
 * \memberof tmap
 */
gtype *tinsert(struct tmap *t, const gtype key, const gtype value);

/**
 * Nếu key không có trong t thì bỏ qua, nếu ngược lại thì xóa cặp
 * khóa & giá trị tương ứng trong t, fk và fv
 * được gọi nếu != NULL.
 *
 * @param t - Con trỏ tới bảng cây.
 * @param key - Khóa cần xóa.
 * @return Chuyển tiếp con trỏ t nếu thành công, hoặc NULL
 * nếu không xóa được (key không có trong bảng).
 *
 * \memberof tmap
 *
 */
struct tmap *tremove(struct tmap *t, gtype key);

/**
 * Truy vấn kích thước (số lượng phần tử) của cây.
 * 
 * @param t - Con trỏ tới cây.
 * @return Số lượng phần tử của cây.
 * \memberof tmap
 */
long tsize(const struct tmap *t);

/**
 * Truy cập con trỏ tới value khi biết con trỏ tới key
 * 
 * @param key - Con trỏ tới khóa của nút.
 * @return Con trỏ tới giá trị của nút.
 * \memberof tmap
 */
gtype *tvalue(gtype *key);

/**
 * Lấy phần tử trái nhất của 1 nút.
 * 
 * @param n - Con trỏ tới 1 nút.
 * @return Con trỏ tới nút trái nhất trong cây con
 * với gốc là n.
 * \memberof tnode
 */
struct tnode *tlmost(struct tnode *n);

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
 * Dịch chuyển sang nút kế tiếp theo thứ tự 
 * trái-phải-nút.
 * 
 * @param pk - Con trỏ tới con trỏ tới khóa hiện tại.
 * @param pv - Con trỏ tới con trỏ tới giá trị hiện tại.
 * @return Không trả về giá trị.
 * \memberof tnode
 */
void tnext_lrn(gtype **pk, gtype **pv);

/** 
 * Tìm nút liền sau của x
 * 
 * @param x - Con trỏ tới 1 nút của cây.
 * @return Trả về con trỏ tới nút liền sau nếu có,
 * hoặc NULL nếu không.
 * \memberof tnode
 */
struct tnode *tnextin(struct tnode *x);

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

/**
 * Truy cập gốc của cây
 * 
 * @param t - Con trỏ tới cây.
 * @return Trả về con trỏ tới gốc của cây.
 * \memberof tmap
 */
struct tnode *troot(struct tmap *t);

/**
 * Dịch chuyển cặp khóa và giá trị sang vị trí tiếp theo theo chiều
 * thuận (hỗ trợ triển khai #TTRAVERSE)
 * 
 * @param pk - Con trỏ tới con trỏ tới khóa.
 * @param pv - Con trỏ tới con trỏ tới giá trị tương ứng.
 * @return Không trả về giá trị.
 * \memberof tmap
 */
void tnext(gtype **k, gtype **v);

/**
 * Giải phóng bộ nhớ của bảng cây.
 * 
 * @param t - Con trỏ tới bảng.
 * @return Không trả về giá trị.
 */
void tfree(struct tmap *t);

/**
 * Duyệt tuần tự các cặp khóa & giá trị trong bảng t. Các tham số k và v
 * là các định danh do người sử dụng tự đặt và sẽ có kiểu \ref gtype *
 *
 * @param k Định danh sẽ được sử dụng như con trỏ tới khóa hiện hành.
 * @param v Định danh sẽ được sử dụng như con trỏ tới giá trị hiện hành.
 * @param t Con trỏ tới bảng cây.
 *
 */
#define TTRAVERSE(k, v, t) \
  for (gtype *k = (gtype*)tlmost(troot(t)), \
             *v = k? tvalue(k): NULL; \
       k != NULL && v != NULL; tnext(&k, &v))

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
             *v = k? tvalue(k): NULL; \
       k != NULL; tnext_lrn(&k, &v))

#endif  // CONT_TREEMAP_H_