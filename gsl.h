#ifndef GSL_H_
#define GSL_H_

/*
  (C) Nguyen Ba Ngoc 2021
  gtype single linked list
*/

#include "base/sll.h"
#include "gtype.h"

typedef struct sll_node_g_s {
  struct sll_node_s base;
  gtype value;
} *sll_node_g_t;

sll_node_t sll_create_node_g(gtype value);
void sll_push_back_g(sll_t list, gtype value);
void sll_push_front_g(sll_t list, gtype value);
gtype sll_pop_front_g(sll_t list);
gtype sll_front_g(sll_t list);

#define to_sll_node_g(n) ((sll_node_g_t)n)
#define sll_node_g_value(n) (to_sll_node_g(n)->value)

#endif  // GSL_H_
