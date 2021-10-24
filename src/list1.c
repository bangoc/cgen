#include "list1.h"

list1_t list1_create() {
  list1_t l = calloc(1, sizeof(struct list1_s));
  return l;
}

list1_t list1_append(list1_t list, list1_node_t node) {
  node->next = NULL;
  if (list->first == NULL) {
    list->first = list->last = node;
  } else {
    list->last->next = node;
    list->last = node;
  }
  list->size++;
  return list;
}

list1_t list1_prepend(list1_t list, list1_node_t node) {
  if (list->first == NULL) {
    list->first = list->last = node;
    node->next = NULL;
  } else {
    node->next = list->first;
    list->first = node;
  }
  ++list->size;
  return list;
}

list1_node_t list1_remove_first(list1_t list) {
  if (list->size == 0) {
    return NULL;
  }
  list1_node_t node = list->first;
  list->first = list->first->next;
  --list->size;
  if (list->size == 0) {
    list->last = NULL;
  }
  return node;
}

bool list1_empty(list1_t list) {
  return list->size == 0;
}

/* Triển khai giao diện gtype */

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

/* Triển khai giao diện stack số nguyên */
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

/* Triển khai giao diện queue số nguyên */
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