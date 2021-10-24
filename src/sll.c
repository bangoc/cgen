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
  list->size++;
}

void sll_push_front(sll_t list, sll_node_t node) {
  if (list->front == NULL) {
    list->front = list->back = node;
    node->next = NULL;
  } else {
    node->next = list->front;
    list->front = node;
  }
  ++list->size;
}

void sll_pop_front(sll_t list) {
  if (list->size == 0) {
    return;
  }
  sll_node_t tmp = list->front;
  list->front = list->front->next;
  --list->size;
  if (list->size == 0) {
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
  return list->size == 0;
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