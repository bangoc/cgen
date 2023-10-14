/* (C) Nguyễn Bá Ngọc 2023 */

#include "dlist.h"

#include <stdlib.h>

/**
 * Cấu trúc mô tả nút của danh sách móc nối kép.
 * dnode = double linked node
 */
struct dnode {
  gtype data;
  struct dnode *next;
  struct dnode *prev;
};

/**
 * Cấu trúc mô tả danh sách móc nối kép
 * dlist = double linked list
 */
struct dlist {
  struct dnode *front;
  struct dnode *back;
  long length;
  gtype_free_t fv;
};

struct dnode *dnode(gtype data) {
  struct dnode *tmp = malloc(sizeof(struct dnode));
  if (!tmp) {
#ifdef CGEN_DEBUG
    flog("Không thể cấp phát bộ nhớ cho nút.");
#endif  // CGEN_DEBUG
    return NULL;
  }
  tmp->data = data;
  tmp->next = tmp->prev = NULL;
  return tmp;
}

struct dlist *dcreate() {
  struct dlist *tmp = malloc(sizeof(struct dlist));
  if (!tmp) {
#ifdef CGEN_DEBUG
    flog("Không thể cấp phát bộ nhớ cho danh sách.");
#endif  // CGEN_DEBUG
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

void dfree(struct dlist *list) {
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
  struct dnode *nn = dnode(elem);
  if (!nn) {
#ifdef CGEN_DEBUG
    flog("Lỗi không thể tạo nút.");
#endif  // CGEN_DEBUG  
    return NULL;  
  }
  if (!list) {
#ifdef CGEN_DEBUG
    flog("Lỗi không thể tạo nút.");
#endif  // CGEN_DEBUG  
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
  struct dnode *nn = dnode(elem);
  if (!nn) {
#ifdef CGEN_DEBUG
    flog("Lỗi không thể tạo nút.");
#endif  // CGEN_DEBUG  
    return NULL;  
  }
  if (!list) {
#ifdef CGEN_DEBUG
    flog("Lỗi không thể tạo nút.");
#endif  // CGEN_DEBUG  
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
#ifdef CGEN_DEBUG
    flog("Lỗi danh sách không hợp lệ.");
#endif  // CGEN_DEBUG    
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
    list->fv((gtype*)tmp);
  }
  free(tmp);
  --list->length;
  return list;
}

struct dlist *ddback(struct dlist *list) {
  if (!list || dempty(list)) {
#ifdef CGEN_DEBUG
    flog("Lỗi danh sách không hợp lệ.");
#endif  // CGEN_DEBUG    
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
    list->fv((gtype*)tmp);
  }
  free(tmp);
  --list->length;
  return list;
}

gtype_free_t dfv(struct dlist *list) {
  return list->fv;
}

struct dlist *dsetfv(struct dlist *list, gtype_free_t fv) {
  if (!list) {
#ifdef CGEN_DEBUG
    flog("Lỗi danh sách không hợp lệ.");
#endif  // CGEN_DEBUG    
    return NULL;    
  }
  list->fv = fv;
  return list;
}