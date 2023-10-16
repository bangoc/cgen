/* (C) Nguyen Ba Ngoc 2023 */

#ifdef CGEN_DEBUG
#include "base/flog.h"
#endif  // CGEN_DEBUG

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
  gtype_free_t fv;

  /** Độ dài (số lượng phần tử) của danh sách */
  long length;
};

struct snode *snode(gtype data) {
  struct snode *tmp = malloc(sizeof(struct snode));
  if (!tmp) {
#ifdef CGEN_DEBUG
    FLOG("Lỗi cấp phát bộ nhớ tạo nút.");
#endif  // CGEN_DEBUG
    return NULL;
  }
  tmp->data = data;
  tmp->next = NULL;
  return tmp;
}

struct slist *screate() {
  struct slist *tmp = malloc(sizeof(struct slist));
  if (!tmp) {
#ifdef CGEN_DEBUG
    FLOG("Lỗi cấp phát bộ nhớ tạo danh sách.");
#endif  // CGEN_DEBUG
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

struct slist *sappend(struct slist *list, gtype data) {
  struct snode *node = snode(data);
  if (!node) {
#ifdef CGEN_DEBUG
    FLOG("Lỗi tạo nút");
#endif  // CGEN_DEBUG   
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

struct slist *sprepend(struct slist *list, gtype data) {
  struct snode *node = snode(data);
  if (!node) {
#ifdef CGEN_DEBUG
    FLOG("Lỗi tạo nút");
#endif  // CGEN_DEBUG   
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
#ifdef CGEN_DEBUG
    FLOG("Xóa đầu danh sách không hợp lệ.");
#endif  // CGEN_DEBUG    
    return NULL;
  }
  if (list->front == list->back) {
    list->back = NULL;
  }
  struct snode *tmp = list->front;
  list->front = tmp->next;
  if (list->fv) {
    list->fv((gtype*)tmp);
  }
  free(tmp);
  --list->length;
  return list;
}

gtype_free_t sfv(struct slist *list) {
  return list->fv;
}

struct slist *ssetfv(struct slist *list, gtype_free_t fv) {
  list->fv = fv;
  return list;
}

void sfree(struct slist *list) {
  while (!sempty(list)) {
    sdfront(list);
  }
  free(list);
}

struct slist *spush(struct slist *list, gtype elem) {
  return sprepend(list, elem);
}

struct slist *spop(struct slist *list) {
  return sdfront(list);
}

gtype *stop(struct slist *list) {
  if (list == NULL || sempty(list)) {
#ifdef CGEN_DEBUG
    FLOG("Ngăn xếp ở trạng thái không hợp lệ.");
#endif  // CGEN_DEBUG    
    return NULL;
  }
  return sfront(list);
}

struct slist *senque(struct slist *list, gtype elem) {
  return sappend(list, elem);
}

struct slist *sdeque(struct slist *list) {
  return sdfront(list);
}

gtype *speek(struct slist *list) {
  if (list == NULL || sempty(list)) {
#ifdef CGEN_DEBUG
    FLOG("hàng đợi ở trạng thái không hợp lệ.");
#endif  // CGEN_DEBUG    
    return NULL;
  }
  return sfront(list);
}