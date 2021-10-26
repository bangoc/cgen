/*
  (C) 2021 Nguyen Ba Ngoc
  Singly Linked List (SLL/sll) and its derived types
*/

#ifndef SLL_H_
#define SLL_H_

typedef struct sll_node_s {
  struct sll_node_s *next;
} *sll_node_t;

typedef struct sll_s {
  sll_node_t front;
  sll_node_t back;
  void (*fn)();  // Hàm giải phóng bộ nhớ cho nút
} *sll_t;

sll_node_t sll_create_node();
void sll_free_node(sll_node_t node);
sll_t sll_create_list();
void sll_free_list(sll_t list);

void sll_push_back(sll_t list, sll_node_t node);
void sll_push_front(sll_t list, sll_node_t node);
void sll_pop_front(sll_t list);
sll_node_t sll_front(sll_t list);
int sll_is_empty(sll_t list);
long sll_length(sll_t list);

void sll_pprint_node(sll_node_t node);
void sll_pprint_list(sll_t list);

#define sll_traverse(cur, list) \
  for (sll_node_t cur = list->front; cur != NULL; cur = cur->next)

/* Giao diện gtype */

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

/* Giao diện stack kiểu long dựa trên sll */

typedef struct sll_node_l_s {
  struct sll_node_s base;
  long value;
} *sll_node_l_t;

void sll_pprint_node_l(sll_node_t node);
void sll_pprint_list_l(sll_t list);

#define to_sll_node_l(n) ((sll_node_l_t)n)
#define sll_node_l_value(n) (to_sll_node_l(n)->value)

sll_node_t sll_create_node_l(long value);
void sll_stack_push_l(sll_t list, long value);
long sll_stack_pop_l(sll_t list);
long sll_stack_top_l(sll_t list);

/* Giao diện queue kiểu long dựa trên giao diện sll */
void sll_fifo_enqueue_l(sll_t list, long value);
long sll_fifo_dequeue_l(sll_t list);
long sll_fifo_peek_l(sll_t list);

#endif  // SLL_H_