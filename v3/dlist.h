/* (C) Nguyễn Bá Ngọc 2025 */

#ifndef DLIST_H_
#define DLIST_H_

#include <stdio.h>
#include <stdlib.h>

#define DLIST_DECL(sname, elem_t) \
struct sname##_node; \
struct sname; \
struct sname##_node *sname##_node(elem_t value); \
struct sname *sname(); \
struct sname *sname##_append(struct sname *list, elem_t value); \
struct sname *sname##_prepend(struct sname *list, elem_t value); \
int sname##_ins(struct sname *list, elem_t value, int idx); \
int sname##_insa(struct sname *list, elem_t value, struct sname##_node *node); \
int sname##_insb(struct sname *list, elem_t value, struct sname##_node *node); \
struct sname##_node *sname##_at(struct sname *list, int idx); \
struct sname *sname##_dfirst(struct sname *list); \
struct sname *sname##_dlast(struct sname *list); \
struct sname *sname##_dnode(struct sname *list, struct sname##_node *node); \
int sname##_del(struct sname *list, int idx); \
int sname##_empty(struct sname *list); \
void sname##_free(struct sname *list);

#define DLIST_IMPL(sname, elem_t) \
struct sname##_node { \
  elem_t value; \
  struct sname##_node *next; \
  struct sname##_node *prev; \
}; \
struct sname { \
  struct sname##_node *first; \
  struct sname##_node *last; \
  int size; \
}; \
\
struct sname##_node *sname##_node(elem_t value) { \
  struct sname##_node *nn = malloc(sizeof(struct sname##_node)); \
  nn->value = value; \
  nn->next = NULL; \
  nn->prev = NULL; \
  return nn; \
} \
struct sname *sname() { \
  struct sname *dll = malloc(sizeof(struct sname)); \
  dll->first = dll->last = NULL; \
  dll->size = 0; \
  return dll; \
} \
void sname##_free(struct sname *list) { \
  struct sname##_node *p = list->first, *n; \
  while (p) { \
    n = p->next; \
    free(p); \
    p = n; \
  } \
  free(list); \
} \
struct sname *sname##_append(struct sname *list, elem_t value) {\
  struct sname##_node *nn = sname##_node(value); \
  if (!nn) { \
    return NULL; \
  } \
  if (list->first == NULL) { \
    list->first = list->last = nn; \
  } else { \
    list->last->next = nn; \
    nn->prev = list->last; \
    list->last = nn; \
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
    list->first->prev = node; \
    list->first = node; \
  } \
  ++list->size; \
  return list; \
} \
int sname##_ins(struct sname *list, elem_t value, int idx) { \
  if (!list || idx < 0 || idx > list->size) { \
    return 1; \
  } \
  if (idx == 0) { \
    sname##_prepend(list, value); \
    return 0; \
  } \
  if (idx == list->size) { \
    sname##_append(list, value); \
    return 0; \
  } \
  struct sname##_node *p = sname##_at(list, idx - 1), *nn = sname##_node(value); \
  nn->next = p->next; \
  p->next->prev = nn; \
  p->next = nn; \
  nn->prev = p; \
  ++list->size; \
  return 0; \
} \
int sname##_insa(struct sname *list, elem_t value, struct sname##_node *pos) { \
  if (!list) { \
    return 1; \
  } \
  if (pos == list->last) { \
    sname##_append(list, value); \
    return 0; \
  } \
  if (!pos) { \
    return 1; \
  } \
  struct sname##_node *nn = sname##_node(value); \
  nn->next = pos->next; \
  pos->next->prev = nn; \
  pos->next = nn; \
  nn->prev = pos; \
  ++list->size; \
  return 0; \
} \
int sname##_insb(struct sname *list, elem_t value, struct sname##_node *pos) { \
  if (!list) { \
    return 1; \
  } \
  if (pos == list->first) { \
    sname##_prepend(list, value); \
    return 0; \
  } \
  if (!pos) { \
    return 1; \
  } \
  struct sname##_node *nn = sname##_node(value); \
  nn->prev = pos->prev; \
  pos->prev->next = nn; \
  nn->next = pos; \
  pos->prev = nn; \
  ++list->size; \
  return 0; \
} \
struct sname##_node *sname##_at(struct sname *list, int idx) { \
  if (!list || idx < 0 || idx >= list->size) { \
    return NULL; \
  } \
  struct sname##_node *n = list->first; \
  for (int i = 1; i <= idx; ++i) { \
    n = n->next; \
  } \
  return n; \
} \
struct sname *sname##_dfirst(struct sname *list) { \
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
struct sname *sname##_dlast(struct sname *list) { \
  if (!list || list->last == NULL) { \
    return NULL; \
  } \
  if (list->first == list->last) { \
    list->first = NULL; \
  } \
  struct sname##_node *tmp = list->last; \
  list->last = tmp->prev; \
  free(tmp); \
  --list->size; \
  return list; \
} \
struct sname *sname##_dnode(struct sname *list, struct sname##_node *node) { \
  if (!node) { \
    return NULL; \
  } \
  if (node == list->first) {  \
    return sname##_dfirst(list); \
  } \
  if (node == list->last) { \
    return sname##_dlast(list); \
  } \
  struct sname##_node *prev = node->prev, *next = node->next; \
  prev->next = next; \
  next->prev = prev; \
  free(node); \
  --list->size; \
  return list; \
} \
int sname##_del(struct sname *list, int idx) { \
  if (!list || idx < 0 || idx >= list->size) { \
    return 1; \
  } \
  if (idx == 0) { \
    sname##_dfirst(list); \
    return 0; \
  } \
  struct sname##_node *n = sname##_at(list, idx); \
  sname##_dnode(list, n); \
  return 0; \
} \
int sname##_empty(struct sname *list) { \
  return list->first == NULL || list->last == NULL; \
}

#define DLIST_DECL_IMPL(sname, elem_t) \
DLIST_DECL(sname, elem_t) \
DLIST_IMPL(sname, elem_t)

#endif  // DLIST_H_