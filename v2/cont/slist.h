/* (C) Nguyen Ba Ngoc 2023 */

#ifndef CONT_SLIST_H_
#define CONT_SLIST_H_

/** @file
 * @brief Triển khai danh sách móc nối đơn với gtype
 */

#include "base/core.h"
#include "base/gtype.h"

/**
 * Hàm tạo danh sách
 * 
 * @return Trả về con trỏ tới danh sách nếu thành công,
 * hoặc NULL nếu không thể cấp phát bộ nhớ.
 */
struct slist *screate();

/**
 * Hàm truy cập nút đầu tiên của danh sách 
 * 
 * @return con trỏ list->front
 */
gtype *sfront(struct slist *list);

/**
 * Hàm truy cập nút cuối cùng trong danh sách
 * 
 * @return con trỏ list->back
 */
gtype *sback(struct slist *list);

/**
 * Hàm truy cập độ dài danh sách
 * 
 * @return Giá trị list->length
 */
long ssize(struct slist *list);

/**
 * Truy cập con trỏ fv của list
 * 
 * @return Con trỏ fv.
 */
gtype_free_t sfv(struct slist *list);

/**
 * Thiết lập con trỏ fv của list
 * 
 * @param list - Con trỏ tới danh sách.
 * @param fv - Con trỏ tới hàm giải phóng bộ nhớ.
 * @return Chuyển tiếp con trỏ list
 */
struct slist *ssetfv(struct slist *list, gtype_free_t fv);

/**
 * Hàm giải phóng bộ nhớ của danh sách
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Hàm không trả về giá trị.
 */
void sfree(struct slist *list);

/**
 * Hàm kiểm tra danh sách rỗng hay không
 * 
 * @param list - Con trỏ tới danh sách
 * @returrn Trả về 1 nếu danh sách rỗng, 0 nếu ngược lại.
 */
int sempty(struct slist *list);

/**
 * Hàm bổ xung phần tử vào cuối danh sách
 * 
 * @param list - Con trỏ tới danh sách móc nối đơn.
 * @param data - Phần tử được thêm vào.
 * @return Chuyển tiếp con trỏ list nếu thành công, hoặc NULL 
 * nếu thất bại.
 */
struct slist *sappend(struct slist *list, gtype data);

/**
 * Hàm bổ xung phần tử vào đầu danh sách
 * 
 * @param list - Con trỏ tới danh sách móc nối đơn.
 * @param data - Phần tử được thêm vào.
 * @return Chuyển tiếp con trỏ list nếu thành công, hoặc NULL
 * nếu thất bại.
 */
struct slist *sprepend(struct slist *list, gtype data);

/**
 * Hàm xóa phần tử đầu tiên của danh sách
 * 
 * @param list - Con trỏ tới danh sách móc nối đơn.
 * @return Chuyển tiếp con trỏ list nếu hợp lệ, hoặc NULL nếu
 * list rỗng hoặc NULL.
 */
struct slist *sdfront(struct slist *list);

/**
 * Macro duyệt các phần tử của danh sách
 */
#define straverse(cur, list) \
  for (gtype *cur = (gtype*)sfront(list); cur != NULL; \
              cur = (gtype*)((struct snode*)cur)->next)

/*** Giao diện ngăn xếp ***/

/**
 * Thêm phần tử vào ngăn xếp.
 * 
 * @param list - Con trỏ tới danh sách.
 * @param elem - Phần tử được thêm vào.
 * @return Chuyển tiếp con trỏ list, hoặc trả về NULL nếu 
 * list ở trạng thái không hợp lệ.
 */
struct slist *spush(struct slist *list, gtype elem);

/**
 * Xóa phần tử khỏi ngăn xếp
 * 
 * @param list - Con trỏ tới ngăn xếp.
 * @return Chuyển tiếp con trỏ list, hoặc trả về NULL nếu 
 * list ở trạng thái không hợp lệ.
 */
struct slist *spop(struct slist *list);

/**
 * Đọc đỉnh của ngăn xếp.
 * 
 * @param list - Con trỏ tới ngăn xếp.
 * @return Con trỏ tới phần tử ở đỉnh ngăn xếp, hoặc NULL
 * nếu không tồn tại.
 */
gtype *stop(struct slist *list);


/*** Giao diện hàng đợi ***/

/**
 * Thêm phần tử vào hàng đợi
 * 
 * @param list - Con trỏ tới hàng đợi.
 * @param elem - Phần tử được thêm vào.
 * @return Chuyển tiếp con trỏ list, hoặc trả về NULL nếu list ở trạng 
 * thái không hợp lệ.
 */
struct slist *senque(struct slist *list, gtype elem);

/**
 * Xóa phần tử khỏi hàng đợi.
 * 
 * @param list - Con trỏ tới hàng đợi.
 * @return Chuyển tiếp con trỏ list, hoặc trả về NULL nếu 
 * list ở trạng thái không hợp lệ.
 */
struct slist *sdeque(struct slist *list);

/**
 * Đọc phần tử hiện hành trong hàng đợi.
 * 
 * @param list - Con trỏ tới hàng đợi.
 * @return Con trỏ tới phần tử hiện hành nếu có, hoặc NULL
 * nếu không tồn tại.
 */
gtype *speek(struct slist *list);


#endif  // CONT_SLIST_H_
