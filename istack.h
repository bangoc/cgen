#ifndef ISTACK_H_
#define ISTACK_H_

#include "gtlist1.h"

// ========== Khai báo hàm ===============

static list1_t istk_push(list1_t list, long value);
static long istk_pop(list1_t list);
static long istk_top(list1_t list);

// ========== Macro viết nhanh ===========


// ========== Định nghĩa hàm =============

static list1_t istk_push(list1_t list, long value) {
  return gtl_prepend(list, gtl_make_node((gtype){.i = value}));
}

static long istk_pop(list1_t list) {
  gtl_node_t node = gtl_remove_first(list);
  if (node) {
    long value = node->val.i;
    free(node);
    return value;
  }
  return INVALID_VALUE.i;
}

static long istk_top(list1_t list) {
  if (list && list->first) {
    gtl_node_value(list).i;
  }
  return INVALID_VALUE.i;
}

#endif  // ISTACK_H_