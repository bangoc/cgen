/*
  (C) 2021 Nguyen Ba Ngoc
*/

#ifndef LIST1_H_
#define LIST1_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list1_node {
  struct list1_node *next;
} *list1_node_t;

typedef struct list1_s {
  size_t size;
  list1_node_t first, last;
} *list1_t;

// ========== Khai báo hàm ===============

static list1_t list1_create();
static list1_t list1_append(list1_t list, list1_node_t node);
static list1_t list1_prepend(list1_t list, list1_node_t node);
static list1_node_t list1_remove_first(list1_t list);

// ========== Macro viết nhanh ===========


// ========== Định nghĩa hàm =============

static list1_t list1_create() {
  list1_t l = calloc(1, sizeof(struct list1_s));
  return l;
}

static list1_t list1_append(list1_t list, list1_node_t node) {
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

static list1_t list1_prepend(list1_t list, list1_node_t node) {
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

static list1_node_t list1_remove_first(list1_t list) {
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

static bool list1_empty(list1_t list) {
  return list->size == 0;
}

#endif  // LIST1_H_