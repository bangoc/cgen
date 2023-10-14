#ifndef CONT_QUEUE_H_
#define CONT_QUEUE_H_

/* (C) Nguyễn Bá Ngọc 2023 */

#include "base/gtype.h"

/**
 * Tạo hàng đợi.
 * 
 * @param cap - Dung lượng, cap = 0 được mặc định thành 8
 * để đảm bảo elems != NULL
 * @return Con trỏ tới hàng đợi được tạo, hoặc NULL nếu thất bại
 */
struct queue *qcreate(long cap);

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
 * Tham chiếu phần tử hiện hành của hàng đợi
 * 
 * @param q - Con trỏ tới hàng đợi.
 * @return Con trỏ tới phần tử hiện hành, hoặc NULL nếu không 
 * tồn tại.
 */ 
gtype *qpeek(struct queue *q);

/**
 * Kiểm tra xem hàng đợi rỗng hay không
 * 
 * @param q - Con trỏ tới hàng đợi.
 * @return Giá trị != 0 nếu rỗng, hoặc 0 nếu không rỗng.
 */
int qempty(const struct queue *q);

/**
 * Đọc số lượng phần tử đang có trong hàng đợi
 * 
 * @param q - Con trỏ tới hàng đợi.
 * @return Số lượng phần tử đang có trong hàng đợi.
 */
long qsize(const struct queue *q);

/**
 * Chỉ số tiếp theo, cho phép xoay vòng
 * 
 * @param q - Con trỏ tới hàng đợi
 * @param id - chỉ số hiện tại
 * @return Chỉ số tiếp theo. qnext(q, q->cap) == 0
 */
long qnext(const struct queue *q, long id);

/**
 * Giải phóng bộ nhớ được cấp phát cho hàng đợi
 * 
 * @param q - Con trỏ tới hàng đợi
 * @return - Không trả về giá trị
 */
void qfree(struct queue *q);

/**
 * Truy vấn con trỏ hàm fv
 * 
 * @return con trỏ hàm giải phóng bộ nhớ phần tử - fv.
 */
gtype_free_t qfv(struct queue *q);

/**
 * Thiết lập con trỏ hàm giải phóng phần tử.
 * 
 * @param q - Con trỏ tới hàng đợi
 * @param fv - Con trỏ hàm giải phóng bộ nhớ của phần tử
 * @return Chuyển tiếp con trỏ q
 */
struct queue *qsetfv(struct queue *q, gtype_free_t fv);

#endif  // CONT_QUEUE_H_
