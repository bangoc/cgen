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
  destructor_fnt fv; \
  long size; \
}

#define SDECL(sname, dtype, prefix) \
SDEFN(sname, dtype); \
struct sname *prefix##create(); \
void prefix##free(void *po); \
struct sname *prefix##append(struct sname *list, dtype data); \
struct sname *prefix##prepend(struct sname *list, dtype data); \
struct sname *prefix##dfront(struct sname *list); \
struct sname *prefix##push(struct sname *list, dtype elem); \
struct sname *prefix##pop(struct sname *list); \
struct sname *prefix##enque(struct sname *list, dtype elem); \
struct sname *prefix##deque(struct sname *list)

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
void prefix##free(void *po) { \
  struct sname *list = po; \
  while (!SEMPTY(list)) { \
    prefix##dfront(list); \
  } \
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
  if (!list || SEMPTY(list)) { \
    FLOG("Xóa đầu danh sách không hợp lệ."); \
    return NULL; \
  } \
  if (list->front == list->back) { \
    list->back = NULL; \
  } \
  struct sname##_node *tmp = list->front; \
  list->front = tmp->next; \
  if (list->fv) { \
    list->fv(&tmp->data); \
  } \
  free(tmp); \
  --list->size; \
  return list; \
} \
struct sname *prefix##push(struct sname *list, dtype elem) { \
  return prefix##prepend(list, elem); \
} \
struct sname *prefix##pop(struct sname *list) {\
  return prefix##dfront(list); \
} \
struct sname *prefix##enque(struct sname *list, dtype elem) { \
  return prefix##append(list, elem); \
} \
struct sname *prefix##deque(struct sname *list) { \
  return prefix##dfront(list); \
}

#endif  // CONT_SLIST_H_