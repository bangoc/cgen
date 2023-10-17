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
 * Truy cập gốc của cây
 * 
 * @param t - Con trỏ tới cây.
 * @return Trả về con trỏ tới gốc của cây.
 * \memberof tmap
 */
struct tnode *troot(struct tmap *t);

/** 
 * Tìm nút liền sau của x
 * 
 * @param x - Con trỏ tới 1 nút của cây.
 * @return Trả về con trỏ tới nút liền sau nếu có,
 * hoặc NULL nếu không.
 * \memberof tnode
 */
struct tnode *tnextin(struct *x);

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
 * Duyệt tuần tự các cặp khóa & giá trị trong bảng map. Các tham số k và v
 * là các định danh do người sử dụng tự đặt và sẽ có kiểu \ref gtype *
 *
 * @param k Định danh sẽ được sử dụng như con trỏ tới khóa hiện hành.
 * @param v Định danh sẽ được sử dụng như con trỏ tới giá trị hiện hành.
 * @param map Con trỏ tới bảng cây.
 *
 */
#define TTRAVERSE(k, v, map) \
  for (gtype *k = (tsize(map))? (gtype*)tlmost(troot(map)): NULL, \
             *v = k? tvalue(k): NULL; \
       k != NULL && v != NULL; tnext(&k, &v)) \

#endif  // CONT_TREEMAP_H_