#include "gtlist1.h"

gtl_node_t gtl_make_node(gtype value) {
  gtl_node_t node = malloc(sizeof(struct gtl_node));
  node->val = value;
  return node;
}

list1_t gtl_append(list1_t list, gtl_node_t val) {
  return list1_append(list, &val->node);
}

list1_t gtl_prepend(list1_t list, gtl_node_t val) {
  return list1_prepend(list, &val->node);
}

gtl_node_t gtl_remove_first(list1_t list) {
  list1_node_t node = list1_remove_first(list);
  return to_gtl(node);
}