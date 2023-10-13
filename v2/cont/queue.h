#ifndef CONT_QUEUE_H_
#define CONT_QUEUE_H_

/* (C) Nguyễn Bá Ngọc 2023 */

#include "base/gtype.h"

/**
 * Macro điều hướng. Lệnh 1 tham số được điều hướng tới 
 * vcreate1, lệnh 2 tham số được điều hướng tới vcreate2.
 * 
 * * @return Trả về đối tượng tạo được nếu thành công hoặc NULL nếu thất bại.
 * \memberof gvector
 */
#define qcreate(...) \
    select_creator(__VA_ARGS__, qcreate2, qcreate1)(__VA_ARGS__)

/**
 * Tạo hàng đợi.
 * 
 * @param cap - Dung lượng, cap = 0 được tự động chuyển thành 8
 * để đảm bảo elems != NULL
 * @return Con trỏ tới hàng đợi được tạo, hoặc NULL nếu thất bại
 */
struct queue *qcreate1(long cap);

/**
 * Thêm phần tử vào cuối hàng đợi 
 * 
 * @param val - Phần tử được thêm vào.
 * @param q - Con trỏ tới hàng đợi
 * @return Chuyển tiếp con trỏ q
 */
struct queue *qenque(struct queue* q, gtype val);

/**
 * Xóa phần tử khỏi hàng đợi
 * @param q - Con trỏ tới hàng đợi.
 * @return Chuyển tiếp con trỏ q
 */
struct queue *qdeque(struct queue *q);

/**
 * Đọc phần tử ở đầu hàng đợi vào tham số out
 * 
 * @param q - Con trỏ tới hàng đợi.
 * @param out - Con trỏ tới đối tượng lưu giá trị đầu ra.
 */ 
struct queue *qpeek(struct queue *q, gtype *out);

/**
 * Kiểm tra xem hàng đợi rỗng hay không
 * 
 * @param q - Con trỏ tới hàng đợi.
 * @return Giá trị != 0 nếu rỗng, hoặc 0 nếu không rỗng.
 */
int qempty(struct queue *q);

/**
 * Đọc số lượng phần tử đang có trong hàng đợi
 * 
 * @param q - Con trỏ tới hàng đợi.
 * @return Số lượng phần tử đang có trong hàng đợi.
 */
long qsize(struct queue *q);

/**
 * Chỉ số tiếp theo, cho phép xoay vòng
 * 
 * @param q - Con trỏ tới hàng đợi
 * @param id - chỉ số hiện tại
 * @return Chỉ số tiếp theo. qnext(q, q->cap) == 0
 */
long qnext(struct queue *q, long id);

/**
 * Giải phóng bộ nhớ được cấp phát cho hàng đợi
 * 
 * @param q - Con trỏ tới hàng đợi
 * @return - Không trả về giá trị
 */
void qfree(struct queue *q);

#endif  // CONT_QUEUE_H_