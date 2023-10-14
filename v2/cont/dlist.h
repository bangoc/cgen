#ifndef CONT_DLIST_H_
#define CONT_DLIST_H_

/* (C) Nguyen Ba Ngoc, 2021 */

/** @file
 * @brief Triển khai danh sách móc nối kép với các phần tử kiểu gtype
 */

/**
 * Hàm tạo danh sách
 * 
 * @return Trả về con trỏ tới danh sách nếu thành công,
 * hoặc NULL nếu không thể cấp phát bộ nhớ.
 */
struct dlist *dcreate();

/**
 * @param list - Con trỏ tới danh sách.
 * @return Con trỏ tới phần tử đầu danh sách nếu tồn tại,
 * hoặc NULL nếu không tồn tại.
 */
gtype *dfront(struct dlist *list);

/**
 * @param list - Con trỏ tới danh sách.
 * @return Con trỏ tới phần tử đầu danh sách nếu tồn tại,
 * hoặc NULL nếu không tồn tại.
 */
gtype *dback(struct dlist *list);

/**
 * @param list - Con trỏ tới danh sách 
 * @return Độ dài - số lượng phần tử trong danh sách
 */
long dsize(struct dlist *list);

#define dtraverse(cur, list) \
  for (gtype *cur = (gtype*)((list)->front); cur != NULL; \
              cur = (gtype*)((struct dnode *)cur->next))

#define drtraverse(cur, list) \
  for (gtype *cur = (gtype*)((list)->back); cur != NULL; \
              cur = (gtype*)((struct dnode *)cur->prev))

/**
 * Kiểm tra danh sách rỗng hay không.
 * 
 * @param list - Con trỏ tới danh sách.
 * @return 1 nếu danh sách rỗng, 0 nếu ngược lại.
 */
int dempty(struct dlist *list);

/**
 * Giải phóng bộ nhớ được cấp phát cho danh sách 
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Hàm không trả về giá trị.
 */
void dfree(struct dlist *list);


/**
 * Làm rỗng danh sách nhưng không giải phóng bộ nhớ
 * của đối tượng danh sách.
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Hàm không trả về giá trị.
 */
void dclear(struct dlist *list);

/**
 * Thêm phần tử vào cuối danh sách
 * 
 * @param list - Con trỏ tới danh sách 
 * @param elem - Phần tử được thêm vào.
 * @return Chuyển tiếp con trỏ list, hoặc NULL nếu 
 * không thể thêm vào danh sách.
 */
struct dlist *dappend(struct dlist *list, gtype elem);

/**
 * Thêm phần tử vào đầu danh sách
 * 
 * @param list - Con trỏ tới danh sách 
 * @param elem - Phần tử được thêm vào.
 * @return Chuyển tiếp con trỏ list, hoặc NULL nếu 
 * không thể thêm vào danh sách.
 */
struct dlist *dprepend(struct dlist *list, gtype elem);

/**
 * Xóa phần tử ở đầu danh sách.
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Chuyển tiếp con trỏ list hoặc trả về NULL
 * nếu tham số không hợp lệ.
 */
struct dlist *ddfront(struct dlist *list);

/**
 * Xóa phần tử ở cuối danh sách.
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Chuyển tiếp con trỏ list hoặc trả về NULL
 * nếu tham số không hợp lệ.
 */
struct dlist *ddback(struct dlist *list);

/**
 * Truy cập con trỏ fv
 * 
 * @param list - Con trỏ tới danh sách.
 * @return Trả về con trỏ fv.
 */
gtype_free_t dfv(struct dlist *list);

/**
 * Thiết lập con trỏ fv
 * 
 * @param list - Con trỏ tới danh sách.
 * @param fv - Con trỏ tới hàm giải phóng bộ nhớ phần tử.
 * @return - Chuyển tiếp con trỏ list nếu thành công,
 * hoặc NULL nếu tham số list không hợp lệ.
 */
struct dlist *dsetfv(struct dlist *list, gtype_free_t fv);

#endif  // CONT_DLIST_H_
