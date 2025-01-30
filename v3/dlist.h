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
struct sname *sname##_ins(struct sname *list, elem_t value, int idx); \
struct sname *sname##_insa(struct sname *list, elem_t value, struct sname##_node *node); \
struct sname *sname##_insb(struct sname *list, elem_t value, struct sname##_node *node); \
struct sname##_node *sname##_at(struct sname *list, int idx); \
int sname##_dfirst(struct sname *list); \
int sname##_dlast(struct sname *list); \
int sname##_dnode(struct sname *list, struct sname##_node *node); \
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
  struct sname##_node *nn = sname##_node(value); \
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
struct sname *sname##_ins(struct sname *list, elem_t value, int idx) { \
  if (!list || idx < 0 || idx > list->size) { \
    return list; \
  } \
  if (idx == 0) { \
    return sname##_prepend(list, value); \
  } \
  if (idx == list->size) { \
    return sname##_append(list, value); \
  } \
  struct sname##_node *p = sname##_at(list, idx - 1), *nn = sname##_node(value); \
  nn->next = p->next; \
  p->next->prev = nn; \
  p->next = nn; \
  nn->prev = p; \
  ++list->size; \
  return list; \
} \
struct sname *sname##_insa(struct sname *list, elem_t value, struct sname##_node *pos) { \
  if (!list) { \
    return list; \
  } \
  if (pos == list->last) { \
    return sname##_append(list, value); \
  } \
  if (!pos) { \
    return list; \
  } \
  struct sname##_node *nn = sname##_node(value); \
  nn->next = pos->next; \
  pos->next->prev = nn; \
  pos->next = nn; \
  nn->prev = pos; \
  ++list->size; \
  return list; \
} \
struct sname *sname##_insb(struct sname *list, elem_t value, struct sname##_node *pos) { \
  if (!list) { \
    return list; \
  } \
  if (pos == list->first) { \
    return sname##_prepend(list, value); \
  } \
  if (!pos) { \
    return list; \
  } \
  struct sname##_node *nn = sname##_node(value); \
  nn->prev = pos->prev; \
  pos->prev->next = nn; \
  nn->next = pos; \
  pos->prev = nn; \
  ++list->size; \
  return list; \
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
int sname##_dfirst(struct sname *list) { \
  if (!list || sname##_empty(list)) { \
    return 0; \
  } \
  if (list->first == list->last) { \
    list->last = NULL; \
  } \
  struct sname##_node *tmp = list->first; \
  list->first = tmp->next; \
  free(tmp); \
  --list->size; \
  return 1; \
} \
int sname##_dlast(struct sname *list) { \
  if (!list || list->last == NULL) { \
    return 0; \
  } \
  if (list->first == list->last) { \
    list->first = NULL; \
  } \
  struct sname##_node *tmp = list->last; \
  list->last = tmp->prev; \
  free(tmp); \
  --list->size; \
  return 1; \
} \
int sname##_dnode(struct sname *list, struct sname##_node *node) { \
  if (!node) { \
    return 0; \
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
  return 1; \
} \
int sname##_del(struct sname *list, int idx) { \
  if (!list || idx < 0 || idx >= list->size) { \
    return 0; \
  } \
  if (idx == 0) { \
    return sname##_dfirst(list); \
  } \
  struct sname##_node *n = sname##_at(list, idx); \
  return sname##_dnode(list, n); \
} \
int sname##_empty(struct sname *list) { \
  return list->first == NULL || list->last == NULL; \
}

#define DLIST_DECL_IMPL(sname, elem_t) \
DLIST_DECL(sname, elem_t) \
DLIST_IMPL(sname, elem_t)

#endif  // DLIST_H_
