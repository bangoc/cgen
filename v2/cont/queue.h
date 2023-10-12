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

struct queue *qcreate1(long cap);

struct queue *qenque(struct queue* q, gtype val);
struct queue *qdequeue(struct queue *q);
struct queue *qpeek(struct queue *q, gtype *out);



#endif  // CONT_QUEUE_H_