#ifndef VAL_LIST1_H_
#define VAL_LIST1_H_

#include "core.h"
#include "list1.h"
#include "val.h"

typedef struct val1_node_s {
  struct list1_node_s node;
  union gtype val;
} *val1_node_t;

static val1_node_t val1_make_node(union gtype value) {
  val1_node_t node = malloc(sizeof(struct val1_node_s));
  node->val = value;
  return node;
}

static list1_t val1_append(list1_t list, val1_node_t val1) {
  return list1_append(list, &val1->node);
}

static list1_t val1_prepend(list1_t list, val1_node_t val1) {
  return list1_prepend(list, &val1->node);
}

static val1_node_t val1_remove_first(list1_t list) {
  list1_node_t node = list1_remove_first(list);
  val1_node_t val1 = container_of(node, struct val1_node_s, node);
  return val1;
}

#define val1_value(pnode) (container_of(pnode, struct val1_node_s, node)->val)

#endif  // VAL_LIST1_H_