/* (C) Nguyễn Bá Ngọc 2023 */

#ifndef CONT_SLIST_H_
#define CONT_SLIST_H_

#define SDEFN(sname, dtype) \
struct sname##_node { \
  dtype data; \
  struct sname##_node *next; \
}; \
struct sname { \
  struct sname##_node *front; \
  struct sname##_node *back; \
  void (*fv)(dtype); \
  long size; \
}

#define SDECL(sname, dtype, prefix) \
SDEFN(sname, dtype); \
struct sname *prefix##create(); \
struct sname *sname(); \
void prefix##clear(struct sname *list); \
void prefix##free(struct sname *list); \
struct sname *prefix##append(struct sname *list, dtype data); \
struct sname *prefix##prepend(struct sname *list, dtype data); \
struct sname *prefix##dfront(struct sname *list); \
struct sname *prefix##push(struct sname *list, dtype elem); \
dtype *prefix##top(struct sname *list); \
struct sname *prefix##pop(struct sname *list); \
struct sname *prefix##enque(struct sname *list, dtype elem); \
dtype *prefix##peek(struct sname *list); \
struct sname *prefix##deque(struct sname *list); \
int prefix##empty(struct sname *list)

#define SIMPL(sname, dtype, prefix) \
struct sname##_node *sname##_node(dtype data) { \
  struct sname##_node *tmp = malloc(sizeof(struct sname##_node)); \
  if (!tmp) { \
    FLOG("Lỗi cấp phát bộ nhớ tạo nút."); \
    return NULL; \
  } \
  tmp->data = data; \
  tmp->next = NULL; \
  return tmp; \
} \
struct sname *prefix##create() { \
  struct sname *tmp = malloc(sizeof(struct sname)); \
  if (!tmp) { \
    FLOG("Lỗi cấp phát bộ nhớ tạo danh sách."); \
    return NULL; \
  } \
  tmp->front = tmp->back = NULL; \
  tmp->fv = NULL; \
  tmp->size = 0; \
  return tmp; \
} \
struct sname *sname() { \
  return prefix##create(); \
} \
void prefix##clear(struct sname *list) { \
  while (!prefix##empty(list)) { \
    prefix##dfront(list); \
  } \
} \
void prefix##free(struct sname *list) { \
  prefix##clear(list); \
  free(list); \
} \
struct sname *prefix##append(struct sname *list, dtype data) {\
  struct sname##_node *node = sname##_node(data); \
  if (!node) { \
    FLOG("Lỗi tạo nút"); \
    return NULL; \
  } \
  if (list->front == NULL) { \
    list->front = list->back = node; \
  } else { \
    list->back->next = node; \
    list->back = node; \
  } \
  ++list->size; \
  return list; \
} \
struct sname *prefix##prepend(struct sname *list, dtype data) {\
  struct sname##_node *node = sname##_node(data); \
  if (!node) { \
    FLOG("Lỗi tạo nút"); \
    return NULL; \
  } \
  if (list->front == NULL) { \
    list->front = list->back = node; \
  } else { \
    node->next = list->front; \
    list->front = node; \
  } \
  ++list->size; \
  return list; \
} \
struct sname *prefix##dfront(struct sname *list) {\
  if (!list || prefix##empty(list)) { \
    FLOG("Xóa đầu danh sách không hợp lệ."); \
    return NULL; \
  } \
  if (list->front == list->back) { \
    list->back = NULL; \
  } \
  struct sname##_node *tmp = list->front; \
  list->front = tmp->next; \
  if (list->fv) { \
    list->fv(tmp->data); \
  } \
  free(tmp); \
  --list->size; \
  return list; \
} \
struct sname *prefix##push(struct sname *list, dtype elem) { \
  return prefix##prepend(list, elem); \
} \
dtype *prefix##top(struct sname *list) { \
  return &list->front->data; \
} \
struct sname *prefix##pop(struct sname *list) {\
  return prefix##dfront(list); \
} \
struct sname *prefix##enque(struct sname *list, dtype elem) { \
  return prefix##append(list, elem); \
} \
dtype *prefix##peek(struct sname *list) {\
  return &list->front->data; \
} \
struct sname *prefix##deque(struct sname *list) { \
  return prefix##dfront(list); \
} \
int prefix##empty(struct sname *list) { \
  return list->front == NULL || list->back == NULL; \
}

#define SDECL_IMPL(sname, dtype, prefix) \
SDECL(sname, dtype, prefix); \
SIMPL(sname, dtype, prefix)

#endif  // CONT_SLIST_H_
