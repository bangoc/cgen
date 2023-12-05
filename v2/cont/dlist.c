/* (C) Nguyễn Bá Ngọc 2023 */

#include "base/flog.h"
#include "cont/dlist.h"

#include <stdlib.h>

/**
 * Cấu trúc mô tả nút của danh sách móc nối kép.
 * dnode = double linked node
 */
struct dnode {
  /** Dữ liệu lưu trong nút */
  gtype data;

  /** Con trỏ tới nút liền sau */
  struct dnode *next;

  /** Con trỏ tới nút liền trước */
  struct dnode *prev;
};

/**
 * Cấu trúc mô tả danh sách móc nối kép
 * dlist = double linked list
 * 
 * Các macros:
 * 
 *   #DTRAVERSE(cur, list) - Duyệt các phần tử của list theo chiều thuận.
 *   Biến cur sẽ có kiểu \ref gtype *
 * 
 *   #DRTRAVERSE(cur, list) - Duyệt các phần tử của list theo chiều ngược.
 *   Biến cur sẽ có kiểu \ref gtype *
 */
struct dlist {
  /** Con trỏ tới đầu danh sách */
  struct dnode *front;

  /** Con trỏ tới cuối danh sách */
  struct dnode *back;

  /** Độ dài (số lượng phần tử trong danh sách) */
  long length;

  /** Con trỏ hàm giải phóng bộ nhớ ngoài của phần tử */
  destructor_fnt fv;
};

struct dnode *dnode(gtype data) {
  struct dnode *tmp = malloc(sizeof(struct dnode));
  if (!tmp) {
    FLOG("Không thể cấp phát bộ nhớ cho nút.");
    return NULL;
  }
  tmp->data = data;
  tmp->next = tmp->prev = NULL;
  return tmp;
}

struct dlist *dcreate() {
  struct dlist *tmp = malloc(sizeof(struct dlist));
  if (!tmp) {
    FLOG("Không thể cấp phát bộ nhớ cho danh sách.");
    return NULL;
  }  
  tmp->front = tmp->back = NULL;
  tmp->length = 0;
  tmp->fv = NULL;
  return tmp;
}

gtype *dfront(struct dlist *list) {
  return (gtype*)list->front;
}

gtype *dback(struct dlist *list) {
  return (gtype*)list->back;
}

long dsize(struct dlist *list) {
  return list->length;
}

int dempty(struct dlist *list) {
  return dfront(list) == NULL && dback(list) == NULL;
}

void dfree(void *op) {
  struct dlist *list = op;
  while (!dempty(list)) {
    ddfront(list);
  }
  free(list);
}

void dclear(struct dlist *list) {
  while (!dempty(list)) {
    ddfront(list);
  }
}

struct dlist *dappend(struct dlist *list, gtype elem) {
  if (!list) {
    FLOG("Lỗi danh sách chưa khởi tạo.");
    return NULL;
  }
  struct dnode *nn = dnode(elem);
  if (!nn) {
    FLOG("Lỗi không thể tạo nút.");
    return NULL;  
  }
  if (dempty(list)) {
    list->front = list->back = nn;
  } else {
    list->back->next = nn;
    nn->prev = list->back;
    list->back = nn;
  }
  ++list->length;
  return list;
}

struct dlist *dprepend(struct dlist *list, gtype elem) {
  if (!list) {
    FLOG("Lỗi danh sách chưa khởi tạo.");
    return NULL;
  }
  struct dnode *nn = dnode(elem);
  if (!nn) {
    FLOG("Lỗi không thể tạo nút.");
    return NULL;
  }
  if (dempty(list)) {
    list->front = list->back = nn;
  } else {
    list->front->prev = nn;
    nn->next = list->front;
    list->front = nn;
  }
  ++list->length;
  return list;
}

struct dlist *ddfront(struct dlist *list) {
  if (!list || dempty(list)) {
    FLOG("Lỗi truy cập danh sách không hợp lệ.");
    return NULL;
  }
  struct dnode *tmp = list->front;
  if (list->front == list->back) {
    list->front = NULL;
    list->back = NULL;
  } else {
    list->front = tmp->next;
    list->front->prev = NULL;
  }
  if (list->fv) {
    list->fv(tmp->data.v);
  }
  free(tmp);
  --list->length;
  return list;
}

struct dlist *ddback(struct dlist *list) {
  if (!list || dempty(list)) {
    FLOG("Lỗi truy cập danh sách không hợp lệ.");
    return NULL;
  }
  struct dnode *tmp = list->back;
  if (list->back == list->front) {   
    list->front = NULL;
    list->back = NULL;
  } else {
    list->back = tmp->prev;
    list->back->next = NULL;
  }
  if (list->fv) {
    list->fv(tmp->data.v);
  }
  free(tmp);
  --list->length;
  return list;
}

destructor_fnt dfv(struct dlist *list) {
  return list->fv;
}

struct dlist *dsetfv(struct dlist *list, destructor_fnt fv) {
  if (!list) {
    FLOG("Lỗi danh sách chưa khởi tạo.");
    return NULL;    
  }
  list->fv = fv;
  return list;
}