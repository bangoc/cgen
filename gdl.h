#ifndef GDL_H_
#define GDL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  gtype double linked list
*/

#include "base/gtype.h"

typedef enum {
  GDN_VALUE,
  GDN_NEXT,
  GDN_PREV,
  GDN_ELEMENTS
} gdn_elements;

typedef struct gdl_s {
  gtype *front, *back;
  gtype_free_t free_value;
} *gdl_t;

#define gdn_value(n) (*(n))
#define gdn_next(n) (((gtype*)(n) + GDN_NEXT)->g)
#define gdn_prev(n) (((gtype*)(n) + GDN_PREV)->g)
#define gdn_create(nn, value) \
  gtype *nn = malloc(GDN_ELEMENTS * sizeof(gtype)); \
  gdn_value(nn) = (value); \
  gdn_next(nn) = NULL; \
  gdn_prev(nn) = NULL

#define gdl_front(list) ((list)->front)
#define gdl_back(list) ((list)->back)
#define gdl_is_empty(list) (gdl_front(list) == NULL && gdl_back(list) == NULL)
#define gdl_push_front(list, value) \
  do { \
    gdn_create(_nn, value); \
    if (gdl_front(list) == NULL) { \
      gdl_front(list) = gdl_back(list) = _nn; \
    } else { \
      gdn_prev(gdl_front(list)) = _nn; \
      gdn_next(_nn) = gdl_front(list); \
      gdl_front(list) = _nn; \
    } \
  } while (0)

#define gdl_push_back(list, value) \
  do { \
    gdn_create(_nn, value); \
    if (gdl_back(list) == NULL) { \
      gdl_front(list) = gdl_back(list) = _nn; \
    } else { \
      gdn_next(gdl_back(list)) = _nn; \
      gdn_prev(_nn) = gdl_back(list); \
      gdl_back(list) = _nn; \
    } \
  } while (0)

#define gdl_pop_front(list) \
  do { \
    if (gdl_is_empty(list)) { \
      break; \
    } \
    gtype *_tmp = gdl_front(list); \
    gdl_front(list) = gdn_next(_tmp); \
    if (gdl_front(list)) { \
      gdn_prev(gdl_front(list)) = NULL; \
    } else { \
      gdl_back(list) = NULL; \
    } \
    if (list->free_value) { \
      list->free_value(gdn_value(_tmp)); \
    } \
    free(_tmp); \
  } while (0)

#define gdl_pop_back(list) \
  do { \
    if (gdl_is_empty(list)) { \
      break; \
    } \
    gtype *_tmp = gdl_back(list); \
    gdl_back(list) = gdn_prev(_tmp); \
    if (gdl_back(list)) { \
      gdn_next(gdl_back(list)) = NULL; \
    } else { \
      gdl_front(list) = NULL; \
    } \
    if (list->free_value) { \
      list->free_value(gdn_value(_tmp)); \
    } \
    free(_tmp); \
  } while (0)

#define gdl_clear(list) \
  do { \
    while (!gdl_is_empty(list)) { \
      gdl_pop_front(list); \
    } \
  } while (0)

#define gdl_free(list) \
  do { \
    gdl_clear(list); \
    free(list); \
  } while (0)

#define gdl_inserta(list, pos, value) \
  do { \
    if (!(pos)) { \
      gdl_push_back(list, value); \
      break; \
    } \
    gdn_create(_nn, value); \
    gtype *_tmp = gdn_next(pos); \
    gdn_next(pos) = _nn; \
    gdn_prev(_nn) = (pos); \
    gdn_next(_nn) = _tmp; \
    if (_tmp) { \
      gdn_prev(_tmp) = _nn; \
    } else { \
      gdl_back(list) = _nn; \
    } \
  } while (0)

#define gdl_insertb(list, pos, value) \
  do { \
    if (!(pos)) { \
      gdl_push_front(list, value); \
      break; \
    } \
    gdn_create(_nn, value); \
    gtype *_tmp = gdn_prev(pos); \
    gdn_prev(pos) = _nn; \
    gdn_next(_nn) = (pos); \
    gdn_prev(_nn) = _tmp; \
    if (_tmp) { \
      gdn_next(_tmp) = _nn; \
    } else { \
      gdl_front(list) = _nn; \
    } \
  } while (0)

gdl_t gdl_create(gtype_free_t free_value);
long gdl_size(gdl_t list);

#define gdl_traverse(cur, list) \
  for (gtype *cur = gdl_front(list); cur; cur = gdn_next(cur))

#endif  // GDL_H_