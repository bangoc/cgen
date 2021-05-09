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

// ========== Khai báo hàm ===============

static gtl_node_t gtl_make_node(gtype value);
static list1_t gtl_append(list1_t list, gtl_node_t val);
static list1_t gtl_prepend(list1_t list, gtl_node_t val);
static gtl_node_t gtl_remove_first(list1_t list);

// ========== Macro viết nhanh ===========

#define gtl_node_value(pnode) (container_of(pnode, struct gtl_node, node)->val)

// ========== Định nghĩa hàm =============

static gtl_node_t gtl_make_node(gtype value) {
  gtl_node_t node = malloc(sizeof(struct gtl_node));
  node->val = value;
  return node;
}

static list1_t gtl_append(list1_t list, gtl_node_t val) {
  return list1_append(list, &val->node);
}

static list1_t gtl_prepend(list1_t list, gtl_node_t val) {
  return list1_prepend(list, &val->node);
}

static gtl_node_t gtl_remove_first(list1_t list) {
  list1_node_t node = list1_remove_first(list);
  if (node) {
    gtl_node_t val = container_of(node, struct gtl_node, node);
    return val;
  }
  return NULL;
}

#endif  // GT_LIST1_H_