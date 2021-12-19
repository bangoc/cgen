/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "base/sll.h"

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