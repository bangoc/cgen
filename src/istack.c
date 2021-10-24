#include "istack.h"

list1_t istk_push(list1_t list, long value) {
  return gtl_prepend(list, gtl_make_node((gtype){.i = value}));
}

long istk_pop(list1_t list) {
  gtl_node_t node = gtl_remove_first(list);
  if (node) {
    long value = node->val.i;
    free(node);
    return value;
  }
  return INVALID_VALUE.i;
}

long istk_top(list1_t list) {
  if (list && list->first) {
    gtl_node_value(list).i;
  }
  return INVALID_VALUE.i;
}