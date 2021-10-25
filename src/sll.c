/*
  (C) Nguyen Ba Ngoc, 2021
*/

#include "sll.h"

#include <stdlib.h>
#include <stdio.h>

sll_node_t sll_create_node() {
  sll_node_t n = malloc(sizeof(struct sll_node_s));
  n->next = NULL;
  return n;
}

void sll_free_node(sll_node_t node) {
  free(node);
}

sll_t sll_create_list() {
  sll_t list = malloc(sizeof(struct sll_s));
  list->front = NULL;
  list->back = NULL;
  list->fn = sll_free_node;
  return list;
}

void sll_free_list(sll_t list) {
  while (!sll_is_empty(list)) {
    sll_pop_front(list);
  }
  free(list);
}

void sll_push_back(sll_t list, sll_node_t node) {
  node->next = NULL;
  if (list->front == NULL) {
    list->front = list->back = node;
  } else {
    list->back->next = node;
    list->back = node;
  }
}

void sll_push_front(sll_t list, sll_node_t node) {
  if (list->front == NULL) {
    list->front = list->back = node;
    node->next = NULL;
  } else {
    node->next = list->front;
    list->front = node;
  }
}

void sll_pop_front(sll_t list) {
  if (sll_is_empty(list)) {
    return;
  }
  sll_node_t tmp = list->front;
  list->front = list->front->next;
  if (list->front == NULL) {
    list->back = NULL;
  }
  if (list->fn) {
    list->fn(tmp);
  }
}

sll_node_t sll_front(sll_t list) {
  return list->front;
}

int sll_is_empty(sll_t list) {
  return list->front == NULL && list->back == NULL;
}

long sll_length(sll_t list) {
  long len = 0;
  sll_node_t n = sll_front(list);
  while (n) {
    ++len;
    n = n->next;
  }
  return len;
}

void sll_pprint_node(sll_node_t node) {
  printf("[%p]", node);
}


void _sll_pprint_list(sll_t list, void (*pn)()) {
  for (sll_node_t cur = list->front; cur != NULL; cur = cur->next) {
    pn(cur);
    printf(" => ");
  }
  printf("NULL\n");
}

void sll_pprint_list(sll_t list) {
  _sll_pprint_list(list, sll_pprint_node);
}

/* Triển khai giao diện gtype */

sll_node_t sll_create_node_g(gtype value) {
  sll_node_g_t nn = malloc(sizeof(struct sll_node_g_s));
  nn->base.next = NULL;
  nn->value = value;
  return (sll_node_t)nn;
}

void sll_push_back_g(sll_t list, gtype value) {
  sll_node_t node = sll_create_node_g(value);
  sll_push_back(list, node);
}

void sll_push_front_g(sll_t list, gtype value) {
  sll_node_t node = sll_create_node_g(value);
  sll_push_front(list, node);
}

gtype sll_pop_front_g(sll_t list) {
  gtype value = sll_front_g(list);
  sll_pop_front(list);
  return value;
}

gtype sll_front_g(sll_t list) {
  sll_node_t front = sll_front(list);
  return sll_node_g_value(front);
}

/* Triển khai giao diện stack số nguyên */

sll_node_t sll_create_node_l(long value) {
  sll_node_l_t nn = malloc(sizeof(struct sll_node_l_s));
  nn->base.next = NULL;
  nn->value = value;
  return (sll_node_t)nn;
}

void sll_stack_push_l(sll_t list, long value) {
  sll_node_t nn = sll_create_node_l(value);
  return sll_push_front(list, nn);
}

long sll_stack_pop_l(sll_t list) {
  long value = sll_stack_top_l(list);
  sll_pop_front(list);
  return value;
}

long sll_stack_top_l(sll_t list) {
  sll_node_t tmp = sll_front(list);
  return sll_node_l_value(tmp);
}

void sll_pprint_node_l(sll_node_t node) {
  printf("[%ld]", sll_node_l_value(node));
}


void sll_pprint_list_l(sll_t list) {
  _sll_pprint_list(list, sll_pprint_node_l);
}

/* Triển khai giao diện queue số nguyên */
void sll_queue_enqueue_l(sll_t list, long value) {
  sll_node_t nn = sll_create_node_l(value);
  return sll_push_back(list, nn);
}

long sll_queue_dequeue_l(sll_t list) {
  long value = sll_queue_peek_l(list);
  sll_pop_front(list);
  return value;
}

long sll_queue_peek_l(sll_t list) {
  sll_node_t tmp = sll_front(list);
  return sll_node_l_value(tmp);
}