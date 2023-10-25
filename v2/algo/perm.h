#ifndef ALGO_PERM_H_
#define ALGO_PERM_H_

/* (C) Nguyễn Bá Ngọc 2023 */

/**
 * @file
 * @brief Các hàm sinh hoán vị
 */

/**
 * Khởi tạo hoán vị với các chỉ số từ 0 đến n-1
 *
 * @param n - Số lượng phần tử.
 * @return - Con trỏ tới vec-tơ với n phần tử
 * được khởi tạo các giá trị từ 0 tới n- 1,
 * hoặc NULL nếu phát sinh lỗi.
 */

struct vector *create_perm(long n);

/**
 * Tính hoán vị tiếp theo theo thứ tự bảng chữ cái của v.
 *
 * @param v - Con trỏ tới vec-tơ chứa hoán vị hiện tại.
 * @return - Chuyển tiếp con trỏ v nếu hiệu chỉnh thành công,
 * hoặc NULL nếu không tồn tại hoán vị tiếp theo.
 */
struct vector *next_perm(struct vector *v);

/**
 * Tính hoán vị liền trước theo thứ tự bảng chữ cái của v.
 *
 * @param v - Con trỏ tới vec-tơ chứa hoán vị hiện tại.
 * @return - Chuyển tiếp con trỏ v nếu hiệu chỉnh thành công,
 * hoặc NULL nếu không tồn tại hoán vị liền trước.
 */
struct vector *prev_perm(struct vector *v);

/**
 * Kiểm tra có tồn tại hoán vị tiếp theo của v hay không.
 *
 * @param v - Con trỏ tới vec-tơ chứa hoán vị hiện tại.
 * @return - 1 nếu có hoán vị tiếp theo, hoặc 0 nếu không
 * tồn tại hoán vị đó.
 */
int has_next_perm(struct vector *v);

/**
 * Kiểm tra có tồn tại hoán vị liền trước của v hay không.
 *
 * @param v - Con trỏ tới vec-tơ chứa hoán vị hiện tại.
 * @return - 1 nếu có hoán vị liền trước, hoặc 0 nếu không
 * tồn tại hoán vị đó.
 */
int has_prev_perm(struct vector *v);

#endif  // ALGO_PERM_H_