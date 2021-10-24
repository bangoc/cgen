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

list1_t list1_create();
list1_t list1_append(list1_t list, list1_node_t node);
list1_t list1_prepend(list1_t list, list1_node_t node);
list1_node_t list1_remove_first(list1_t list);

#endif  // LIST1_H_