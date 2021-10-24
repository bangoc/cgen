#include "iqueue.h"

list1_t iqu_enqueue(list1_t list, long value) {
  return gtl_append(list, gtl_make_node((gtype){.i = value}));
}

long iqu_dequeue(list1_t list) {
  gtl_node_t node = gtl_remove_first(list);
  if (node) {
    long value = node->val.i;
    free(node);
    return value;
  }
  return INVALID_VALUE.i;
}

long iqu_peek(list1_t list) {
  if (list && list->first) {
    gtl_node_value(list).i;
  }
  return INVALID_VALUE.i;
}