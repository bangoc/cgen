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

/* Giao diện gtype */

#include "gtype.h"

typedef struct gtl_node {
  struct list1_node node;
  gtype val;
} *gtl_node_t;

gtl_node_t gtl_make_node(gtype value);
list1_t gtl_append(list1_t list, gtl_node_t val);
list1_t gtl_prepend(list1_t list, gtl_node_t val);
gtl_node_t gtl_remove_first(list1_t list);

#define to_gtl(n) ((gtl_node_t)n)
#define gtl_node_value(n) to_gtl(n)->val

/* Giao diện stack số nguyên dựa trên giao diện gtype */

list1_t istk_push(list1_t list, long value);
long istk_pop(list1_t list);
long istk_top(list1_t list);

/* Giao diện queue số nguyên dựa trên giao diện gtype */
list1_t iqu_enqueue(list1_t list, long value);
long iqu_dequeue(list1_t list);
long iqu_peek(list1_t list);

#endif  // LIST1_H_