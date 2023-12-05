/* (C) Nguyen Ba Ngoc 2023 */

#include "base/flog.h"
#include "cont/slist.h"

/**
 * Cấu trúc mô tả nút của danh sách móc nối đơn
 * snode = single linked node
 */
struct snode {
  /** Dữ liệu được lưu trong nút */
  gtype data;

  /** Con trỏ tới phần tử liền sau */
  struct snode *next;
};

/**
 * Cấu trúc mô tả danh sách móc nối đơn
 * slist = single linked list
 * 
 * Các Macros:
 *    #STRAVERSE(cur, list) - Duyệt các phần tử của list theo chiều thuận.
 *    Biến cur sẽ có kiểu \ref gtype *
 */
struct slist {
  /** Con trỏ tới phần tử ở đầu danh sách */
  struct snode *front;

  /** Con trỏ tới phần tử ở cuối danh sách */
  struct snode *back;

  /** Con trỏ hàm giải phóng bộ nhớ động của phần tử */
  destructor_fnt fv;

  /** Độ dài (số lượng phần tử) của danh sách */
  long length;
};

struct snode *snode(gtype data) {
  struct snode *tmp = malloc(sizeof(struct snode));
  if (!tmp) {
    FLOG("Lỗi cấp phát bộ nhớ tạo nút.");
    return NULL;
  }
  tmp->data = data;
  tmp->next = NULL;
  return tmp;
}

struct slist *screate() {
  struct slist *tmp = malloc(sizeof(struct slist));
  if (!tmp) {
    FLOG("Lỗi cấp phát bộ nhớ tạo danh sách.");
    return NULL;
  }
  tmp->front = tmp->back = NULL;
  tmp->fv = NULL;
  tmp->length = 0;
  return tmp;
}

gtype *sfront(struct slist *list) {
  return (gtype*)list->front;
}

gtype *sback(struct slist *list) {
  return (gtype*)list->back;
}

long ssize(struct slist *list) {
  return list->length;
}

int sempty(struct slist *list) {
  return list->front == NULL && list->back == NULL;
}

struct slist *_sappend(struct slist *list, gtype data) {
  struct snode *node = snode(data);
  if (!node) {
    FLOG("Lỗi tạo nút");
    return NULL; 
  }
  if (list->front == NULL) {
    list->front = list->back = node;
  } else {
    list->back->next = node;
    list->back = node;
  }
  ++list->length;
  return list;
}

struct slist *_sprepend(struct slist *list, gtype data) {
  struct snode *node = snode(data);
  if (!node) {
    FLOG("Lỗi tạo nút");
    return NULL; 
  }
  if (list->front == NULL) {
    list->front = list->back = node;
  } else {
    node->next = list->front;
    list->front = node;
  }
  ++list->length;
  return list;
}

struct slist *sdfront(struct slist *list) {
  if (!list || sempty(list)) {
    FLOG("Xóa đầu danh sách không hợp lệ.");
    return NULL;
  }
  if (list->front == list->back) {
    list->back = NULL;
  }
  struct snode *tmp = list->front;
  list->front = tmp->next;
  if (list->fv) {
    list->fv(tmp->data.v);
  }
  free(tmp);
  --list->length;
  return list;
}

destructor_fnt sfv(struct slist *list) {
  return list->fv;
}

struct slist *ssetfv(struct slist *list, destructor_fnt fv) {
  list->fv = fv;
  return list;
}

void sfree(void *op) {
  struct slist *list = op;
  while (!sempty(list)) {
    sdfront(list);
  }
  free(list);
}

gtype *stop(struct slist *list) {
  if (list == NULL || sempty(list)) {
    FLOG("Ngăn xếp ở trạng thái không hợp lệ.");
    return NULL;
  }
  return sfront(list);
}

gtype *speek(struct slist *list) {
  if (list == NULL || sempty(list)) {
    FLOG("hàng đợi ở trạng thái không hợp lệ.");
    return NULL;
  }
  return sfront(list);
}