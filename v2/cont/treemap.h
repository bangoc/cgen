#ifndef CONT_TREEMAP_H_
#define CONT_TREEMAP_H_

/* (C) Nguyễn Bá Ngọc 2023 */
/**
 * @file
 * @brief Khai báo giao diện cấu trúc \ref treemap
 */

/**
 * Hàm tạo đối tượng điều khiển bảng cây.
 *
 * @param cmp Hàm so sánh các giá trị khóa, phải != NULL.
 * Tham khảo: gtype_cmp_s(gtype v1, gtype v2).
 * @param free_key Con trỏ tới hàm giải phóng bộ nhớ ngoài được gắn với khóa, tham khảo.
 * gtype_free_s(gtype v). Được gọi khi xóa dữ liệu nếu != NULL. Trong trường hợp không
 * có bộ nhớ ngoài hoặc không cần xóa bộ nhớ ngoài (như tình huống đang chia sẻ bộ nhớ
 * với 1 câu trúc lưu trữ khác) thì để = NULL.
 * @param free_value Con trỏ tới hàm giải phóng bộ nhớ ngoài được gắn với giá trị, tương
 * tự free_key.
 * @return Trả về con trỏ tới bảng cây nếu thành công, hoặc NULL
 * nếu không thể cấp phát bộ nhớ.
 *
 * \memberof treemap
 */
struct treemap *tcreate(gtype_cmp_t cmp);

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
 * \memberof treemap
 */
gtype *tinsert(struct treemap *t, const gtype key, const gtype value);

#endif  // CONT_TREEMAP_H_