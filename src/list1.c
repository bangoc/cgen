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