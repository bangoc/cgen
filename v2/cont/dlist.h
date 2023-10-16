/* (C) Nguyen Ba Ngoc, 2021 */

/** @file
 * @brief Khai báo giao diện danh sách móc nối kép với các phần tử \ref gtype
 */


#ifndef CONT_DLIST_H_
#define CONT_DLIST_H_

/**
 * Hàm tạo danh sách
 * 
 * @return Trả về con trỏ tới danh sách nếu thành công,
 * hoặc NULL nếu không thể cấp phát bộ nhớ.
 * \memberof dlist
 */
struct dlist *dcreate();

/**
 * Tham chiếu của phần tử ở đầu danh sách.
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Con trỏ tới phần tử đầu danh sách nếu tồn tại,
 * hoặc NULL nếu không tồn tại.
 * \memberof dlist
 */
gtype *dfront(struct dlist *list);

/**
 * Tham chiếu của phần tử ở cuối danh sách.
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Con trỏ tới phần tử đầu danh sách nếu tồn tại,
 * hoặc NULL nếu không tồn tại.
 * \memberof dlist
 */
gtype *dback(struct dlist *list);

/**
 * Truy vấn kích thước (số lượng phần tử) của danh sách
 * 
 * @param list - Con trỏ tới danh sách 
 * @return Độ dài - số lượng phần tử trong danh sách
 * \memberof dlist
 */
long dsize(struct dlist *list);

/**
 * Kiểm tra danh sách rỗng hay không.
 * 
 * @param list - Con trỏ tới danh sách.
 * @return 1 nếu danh sách rỗng, 0 nếu ngược lại.
 * \memberof dlist
 */
int dempty(struct dlist *list);

/**
 * Giải phóng bộ nhớ được cấp phát cho danh sách 
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Hàm không trả về giá trị.
 * \memberof dlist
 */
void dfree(struct dlist *list);


/**
 * Làm rỗng danh sách nhưng không giải phóng bộ nhớ
 * của đối tượng danh sách.
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Hàm không trả về giá trị.
 * \memberof dlist
 */
void dclear(struct dlist *list);

/**
 * Thêm phần tử vào cuối danh sách
 * 
 * @param list - Con trỏ tới danh sách 
 * @param elem - Phần tử được thêm vào.
 * @return Chuyển tiếp con trỏ list, hoặc NULL nếu 
 * không thể thêm vào danh sách.
 * \memberof dlist
 */
struct dlist *dappend(struct dlist *list, gtype elem);

/**
 * Thêm phần tử vào đầu danh sách
 * 
 * @param list - Con trỏ tới danh sách 
 * @param elem - Phần tử được thêm vào.
 * @return Chuyển tiếp con trỏ list, hoặc NULL nếu 
 * không thể thêm vào danh sách.
 * \memberof dlist
 */
struct dlist *dprepend(struct dlist *list, gtype elem);

/**
 * Xóa phần tử ở đầu danh sách.
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Chuyển tiếp con trỏ list hoặc trả về NULL
 * nếu tham số không hợp lệ.
 * \memberof dlist
 */
struct dlist *ddfront(struct dlist *list);

/**
 * Xóa phần tử ở cuối danh sách.
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Chuyển tiếp con trỏ list hoặc trả về NULL
 * nếu tham số không hợp lệ.
 * \memberof dlist
 */
struct dlist *ddback(struct dlist *list);

/**
 * Truy cập con trỏ fv
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Trả về con trỏ fv.
 * \memberof dlist
 */
gtype_free_t dfv(struct dlist *list);

/**
 * Thiết lập con trỏ fv
 * 
 * @param list - Con trỏ tới danh sách.
 * @param fv - Con trỏ tới hàm giải phóng bộ nhớ phần tử.
 * @return - Chuyển tiếp con trỏ list nếu thành công,
 * hoặc NULL nếu tham số list không hợp lệ.
 * \memberof dlist
 */
struct dlist *dsetfv(struct dlist *list, gtype_free_t fv);


/**
 * Cấu trúc duyệt theo chiều thuận.
 * 
 * @param cur Con trỏ tới phần tử hiện hành của tiến trình duyệt.
 * @param list Con trỏ tới danh sách.
 */
#define dtraverse(cur, list) \
  for (gtype *cur = (gtype*)((list)->front); cur != NULL; \
              cur = (gtype*)((struct dnode *)cur->next))

/**
 * Cấu trúc duyệt theo chiều ngược.
 * 
 * @param cur Con trỏ tới phần tử hiện hành của tiến trình duyệt.
 * @param list Con trỏ tới danh sách.
 */
#define drtraverse(cur, list) \
  for (gtype *cur = (gtype*)((list)->back); cur != NULL; \
              cur = (gtype*)((struct dnode *)cur->prev))

#endif  // CONT_DLIST_H_
