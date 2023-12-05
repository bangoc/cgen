#ifndef CONT_QUEUE_H_
#define CONT_QUEUE_H_

/* (C) Nguyễn Bá Ngọc 2023 */
/** @file
 * @brief Khai báo giao diện hàng đợi FIFO dựa trên mảng động của \ref gtype
 */

#include "base/core.h"

struct queue;

/**
 * Tạo hàng đợi.
 * 
 * @param cap - Dung lượng, cap = 0 được mặc định thành 8
 * để đảm bảo elems != NULL
 * @return Con trỏ tới hàng đợi được tạo, hoặc NULL nếu thất bại
 * \memberof queue
 */
struct queue *qcreate(long cap);

/**
 * Thêm phần tử vào cuối hàng đợi 
 * 
 * @param val - Phần tử được thêm vào.
 * @param q - Con trỏ tới hàng đợi
 * @return Chuyển tiếp con trỏ q
 * \memberof queue
 */
struct queue *qenque(struct queue* q, gtype val);

/**
 * Xóa phần tử khỏi hàng đợi
 * @param q - Con trỏ tới hàng đợi.
 * @return Chuyển tiếp con trỏ q
 * \memberof queue
 */
struct queue *qdeque(struct queue *q);

/**
 * Tham chiếu phần tử hiện hành của hàng đợi
 * 
 * @param q - Con trỏ tới hàng đợi.
 * @return Con trỏ tới phần tử hiện hành, hoặc NULL nếu không 
 * tồn tại.
 * \memberof queue
 */ 
gtype *qpeek(struct queue *q);

/**
 * Kiểm tra xem hàng đợi rỗng hay không
 * 
 * @param q - Con trỏ tới hàng đợi.
 * @return Giá trị != 0 nếu rỗng, hoặc 0 nếu không rỗng.
 * \memberof queue
 */
int qempty(const struct queue *q);

/**
 * Đọc số lượng phần tử đang có trong hàng đợi
 * 
 * @param q - Con trỏ tới hàng đợi.
 * @return Số lượng phần tử đang có trong hàng đợi.
 * \memberof queue
 */
long qsize(const struct queue *q);

/**
 * Chỉ số tiếp theo, cho phép xoay vòng
 * 
 * @param q - Con trỏ tới hàng đợi
 * @param id - chỉ số hiện tại
 * @return Chỉ số tiếp theo. qnext(q, q->cap) == 0
 * \memberof queue
 */
long qnext(const struct queue *q, long id);

/**
 * Giải phóng bộ nhớ được cấp phát cho hàng đợi
 * 
 * @param op - Con trỏ tới hàng đợi
 * @return - Không trả về giá trị
 * \memberof queue
 */
void qfree(void *op);

/**
 * Truy vấn con trỏ hàm fv
 * 
 * @param q Con trỏ tới hàng đợi.
 * @return Con trỏ hàm giải phóng bộ nhớ phần tử - fv.
 * \memberof queue
 */
destructor_fnt qfv(struct queue *q);

/**
 * Thiết lập con trỏ hàm giải phóng phần tử.
 * 
 * @param q - Con trỏ tới hàng đợi
 * @param fv - Con trỏ hàm giải phóng bộ nhớ của phần tử
 * @return Chuyển tiếp con trỏ q
 * \memberof queue
 */
struct queue *qsetfv(struct queue *q, destructor_fnt fv);

#endif  // CONT_QUEUE_H_
