/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef GT_LIST1_H_
#define GT_LIST1_H_

#include "core.h"
#include "list1.h"
#include "gtype.h"

typedef struct gtl_node {
  struct list1_node node;
  gtype val;
} *gtl_node_t;

gtl_node_t gtl_make_node(gtype value);
list1_t gtl_append(list1_t list, gtl_node_t val);
list1_t gtl_prepend(list1_t list, gtl_node_t val);
gtl_node_t gtl_remove_first(list1_t list);

#define to_gtl(n) ((gtl_node_t)n)
#define gtl_node_value(n) to_gtl(n)->val

#endif  // GT_LIST1_H_