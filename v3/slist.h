#ifndef SLIST_H_
#define SLIST_H_

#include <stdlib.h>

#define SLIST_DECL(sname, elem_t) \
struct sname##_node; \
struct sname; \
struct sname##_node *sname##_node(elem_t value); \
struct sname *sname(); \
void sname##_free(struct sname *list); \
struct sname *sname##_append(struct sname *list, elem_t value); \
struct sname *sname##_prepend(struct sname *list, elem_t value); \
struct sname *sname##_dfirst(struct sname *list); \
struct sname *sname##_push(struct sname *list, elem_t elem); \
elem_t *sname##_top(struct sname *list); \
struct sname *sname##_pop(struct sname *list); \
struct sname *sname##_enque(struct sname *list, elem_t elem); \
elem_t *sname##_peek(struct sname *list); \
struct sname *sname##_deque(struct sname *list); \
int sname##_empty(struct sname *list);

#define SLIST_IMPL(sname, elem_t) \
struct sname##_node { \
  elem_t value; \
  struct sname##_node *next; \
}; \
struct sname { \
  struct sname##_node *first; \
  struct sname##_node *last; \
  int size; \
}; \
\
struct sname##_node *sname##_node(elem_t value) { \
  struct sname##_node *tmp = malloc(sizeof(struct sname##_node)); \
  tmp->value = value; \
  tmp->next = NULL; \
  return tmp; \
} \
struct sname *sname() { \
  struct sname *tmp = malloc(sizeof(struct sname)); \
  tmp->first = tmp->last = NULL; \
  tmp->size = 0; \
  return tmp; \
} \
void sname##_free(struct sname *list) { \
  while (!sname##_empty(list)) { \
    sname##_dfirst(list); \
  } \
  free(list); \
} \
struct sname *sname##_append(struct sname *list, elem_t value) {\
  struct sname##_node *node = sname##_node(value); \
  if (!node) { \
    return NULL; \
  } \
  if (list->first == NULL) { \
    list->first = list->last = node; \
  } else { \
    list->last->next = node; \
    list->last = node; \
  } \
  ++list->size; \
  return list; \
} \
struct sname *sname##_prepend(struct sname *list, elem_t value) {\
  struct sname##_node *node = sname##_node(value); \
  if (!node) { \
    return NULL; \
  } \
  if (list->first == NULL) { \
    list->first = list->last = node; \
  } else { \
    node->next = list->first; \
    list->first = node; \
  } \
  ++list->size; \
  return list; \
} \
struct sname *sname##_dfirst(struct sname *list) {\
  if (!list || sname##_empty(list)) { \
    return NULL; \
  } \
  if (list->first == list->last) { \
    list->last = NULL; \
  } \
  struct sname##_node *tmp = list->first; \
  list->first = tmp->next; \
  free(tmp); \
  --list->size; \
  return list; \
} \
struct sname *sname##_push(struct sname *list, elem_t elem) { \
  return sname##_prepend(list, elem); \
} \
elem_t *sname##_top(struct sname *list) { \
  return &list->first->value; \
} \
struct sname *sname##_pop(struct sname *list) {\
  return sname##_dfirst(list); \
} \
struct sname *sname##_enque(struct sname *list, elem_t elem) { \
  return sname##_append(list, elem); \
} \
elem_t *sname##_peek(struct sname *list) {\
  return &list->first->value; \
} \
struct sname *sname##_deque(struct sname *list) { \
  return sname##_dfirst(list); \
} \
int sname##_empty(struct sname *list) { \
  return list->first == NULL || list->last == NULL; \
}

#define SLIST_DECL_IMPL(sname, elem_t) \
SLIST_DECL(sname, elem_t) \
SLIST_IMPL(sname, elem_t)

#endif  // SLIST_H_