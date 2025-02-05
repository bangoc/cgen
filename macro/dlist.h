/* (C) Nguyễn Bá Ngọc 2025 */

#ifndef DLIST_H_
#define DLIST_H_

#include <stdio.h>
#include <stdlib.h>

#define DLIST_DECL(dlname, elem_t) \
struct dlname##_node; \
struct dlname; \
struct dlname##_node *dlname##_node(elem_t value); \
struct dlname *dlname(); \
struct dlname *dlname##_append(struct dlname *list, elem_t value); \
struct dlname *dlname##_prepend(struct dlname *list, elem_t value); \
struct dlname *dlname##_ins(struct dlname *list, int idx, elem_t value); \
struct dlname *dlname##_insa(struct dlname *list, struct dlname##_node *pos, elem_t value); \
struct dlname *dlname##_insb(struct dlname *list, struct dlname##_node *pos, elem_t value); \
struct dlname##_node *dlname##_at(struct dlname *list, int idx); \
int dlname##_dfirst(struct dlname *list); \
int dlname##_dlast(struct dlname *list); \
int dlname##_dnode(struct dlname *list, struct dlname##_node *node); \
int dlname##_del(struct dlname *list, int idx); \
int dlname##_empty(struct dlname *list); \
void dlname##_free(struct dlname *list);

#define DLIST_IMPL(dlname, elem_t) \
struct dlname##_node { \
  elem_t value; \
  struct dlname##_node *next; \
  struct dlname##_node *prev; \
}; \
struct dlname { \
  struct dlname##_node *first; \
  struct dlname##_node *last; \
  int size; \
}; \
\
struct dlname##_node *dlname##_node(elem_t value) { \
  struct dlname##_node *nn = malloc(sizeof(struct dlname##_node)); \
  nn->value = value; \
  nn->next = NULL; \
  nn->prev = NULL; \
  return nn; \
} \
struct dlname *dlname() { \
  struct dlname *dll = malloc(sizeof(struct dlname)); \
  dll->first = dll->last = NULL; \
  dll->size = 0; \
  return dll; \
} \
void dlname##_free(struct dlname *list) { \
  struct dlname##_node *p = list->first, *n; \
  while (p) { \
    n = p->next; \
    free(p); \
    p = n; \
  } \
  free(list); \
} \
struct dlname *dlname##_append(struct dlname *list, elem_t value) {\
  struct dlname##_node *nn = dlname##_node(value); \
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
struct dlname *dlname##_prepend(struct dlname *list, elem_t value) {\
  struct dlname##_node *nn = dlname##_node(value); \
  if (list->first == NULL) { \
    list->first = list->last = nn; \
  } else { \
    nn->next = list->first; \
    list->first->prev = nn; \
    list->first = nn; \
  } \
  ++list->size; \
  return list; \
} \
struct dlname *dlname##_ins(struct dlname *list, int idx, elem_t value) { \
  if (!list || idx < 0 || idx > list->size) { \
    return list; \
  } \
  if (idx == 0) { \
    return dlname##_prepend(list, value); \
  } \
  if (idx == list->size) { \
    return dlname##_append(list, value); \
  } \
  struct dlname##_node *p = dlname##_at(list, idx - 1), *nn = dlname##_node(value); \
  nn->next = p->next; \
  p->next->prev = nn; \
  p->next = nn; \
  nn->prev = p; \
  ++list->size; \
  return list; \
} \
struct dlname *dlname##_insa(struct dlname *list, struct dlname##_node *pos, elem_t value) { \
  if (!list) { \
    return list; \
  } \
  if (pos == list->last) { \
    return dlname##_append(list, value); \
  } \
  if (!pos) { \
    return list; \
  } \
  struct dlname##_node *nn = dlname##_node(value); \
  nn->next = pos->next; \
  pos->next->prev = nn; \
  pos->next = nn; \
  nn->prev = pos; \
  ++list->size; \
  return list; \
} \
struct dlname *dlname##_insb(struct dlname *list, struct dlname##_node *pos, elem_t value) { \
  if (!list) { \
    return list; \
  } \
  if (pos == list->first) { \
    return dlname##_prepend(list, value); \
  } \
  if (!pos) { \
    return list; \
  } \
  struct dlname##_node *nn = dlname##_node(value); \
  nn->prev = pos->prev; \
  pos->prev->next = nn; \
  nn->next = pos; \
  pos->prev = nn; \
  ++list->size; \
  return list; \
} \
struct dlname##_node *dlname##_at(struct dlname *list, int idx) { \
  if (!list || idx < 0 || idx >= list->size) { \
    return NULL; \
  } \
  struct dlname##_node *n = list->first; \
  for (int i = 1; i <= idx; ++i) { \
    n = n->next; \
  } \
  return n; \
} \
int dlname##_dfirst(struct dlname *list) { \
  if (!list || dlname##_empty(list)) { \
    return 0; \
  } \
  if (list->first == list->last) { \
    list->last = NULL; \
  } \
  struct dlname##_node *tmp = list->first; \
  list->first = tmp->next; \
  free(tmp); \
  --list->size; \
  return 1; \
} \
int dlname##_dlast(struct dlname *list) { \
  if (!list || list->last == NULL) { \
    return 0; \
  } \
  if (list->first == list->last) { \
    list->first = NULL; \
  } \
  struct dlname##_node *tmp = list->last; \
  list->last = tmp->prev; \
  free(tmp); \
  --list->size; \
  return 1; \
} \
int dlname##_dnode(struct dlname *list, struct dlname##_node *node) { \
  if (!node) { \
    return 0; \
  } \
  if (node == list->first) {  \
    return dlname##_dfirst(list); \
  } \
  if (node == list->last) { \
    return dlname##_dlast(list); \
  } \
  struct dlname##_node *prev = node->prev, *next = node->next; \
  prev->next = next; \
  next->prev = prev; \
  free(node); \
  --list->size; \
  return 1; \
} \
int dlname##_del(struct dlname *list, int idx) { \
  if (!list || idx < 0 || idx >= list->size) { \
    return 0; \
  } \
  if (idx == 0) { \
    return dlname##_dfirst(list); \
  } \
  struct dlname##_node *n = dlname##_at(list, idx); \
  return dlname##_dnode(list, n); \
} \
int dlname##_empty(struct dlname *list) { \
  return list->first == NULL || list->last == NULL; \
}

#define DLIST_DECL_IMPL(dlname, elem_t) \
DLIST_DECL(dlname, elem_t) \
DLIST_IMPL(dlname, elem_t)

#endif  // DLIST_H_
