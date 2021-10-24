/*
  (C) 2021 Nguyen Ba Ngoc
  Singly Linked List (SLL/sll) and its derived types
*/

#ifndef SLL_H_
#define SLL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct sll_node_s {
  struct sll_node_s *next;
} *sll_node_t;

typedef struct sll_s {
  size_t size;
  sll_node_t front, back;
} *sll_t;

sll_t sll_create();
sll_t sll_push_back(sll_t list, sll_node_t node);
sll_t sll_push_front(sll_t list, sll_node_t node);
sll_node_t sll_pop_front(sll_t list);
bool sll_empty(sll_t list);

/* Giao diện gtype */

#include "gtype.h"

typedef struct gsl_node_s {
  struct sll_node_s node;
  gtype val;
} *gsl_node_t;

gsl_node_t gsl_make_node(gtype value);
sll_t gsl_push_back(sll_t list, gsl_node_t val);
sll_t gsl_push_front(sll_t list, gsl_node_t val);
gsl_node_t gsl_pop_front(sll_t list);

#define to_gsl(n) ((gsl_node_t)n)
#define gsl_node_value(n) to_gsl(n)->val

/* Giao diện stack số nguyên dựa trên giao diện gtype */

sll_t ist_push(sll_t list, long value);
long ist_pop(sll_t list);
long ist_top(sll_t list);

/* Giao diện queue số nguyên dựa trên giao diện gtype */
sll_t iqu_enqueue(sll_t list, long value);
long iqu_dequeue(sll_t list);
long iqu_peek(sll_t list);

#endif  // SLL_H_