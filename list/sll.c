/* (C) Nguyen Ba Ngoc 2021 */

#include "list/sll.h"

#include <stdlib.h>
#include <stdio.h>

sln_t sln_create() {
  sln_t n = malloc(sizeof(struct sln_s));
  n->next = NULL;
  return n;
}

sll_t sll_create() {
  sll_t list = malloc(sizeof(struct sll_s));
  list->front = NULL;
  list->back = NULL;
  return list;
}

void sll_free(sll_t list) {
  while (!sll_is_empty(list)) {
    sll_pop_front(list);
  }
  free(list);
}

void sll_push_back(sll_t list, sln_t node) {
  node->next = NULL;
  if (list->front == NULL) {
    list->front = list->back = node;
  } else {
    list->back->next = node;
    list->back = node;
  }
}

void sll_push_front(sll_t list, sln_t node) {
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
  sln_t tmp = list->front;
  list->front = list->front->next;
  if (list->front == NULL) {
    list->back = NULL;
  }
  sln_free(tmp);
}

int sll_is_empty(sll_t list) {
  return list->front == NULL && list->back == NULL;
}

long sll_length(sll_t list) {
  long len = 0;
  sln_t n = sll_front(list);
  while (n) {
    ++len;
    n = n->next;
  }
  return len;
}

void sln_pprint(sln_t node) {
  printf("[%p]", node);
}


void _sll_pprint(sll_t list, void (*pn)()) {
  for (sln_t cur = list->front; cur != NULL; cur = cur->next) {
    pn(cur);
    printf(" => ");
  }
  printf("NULL\n");
}

void sll_pprint(sll_t list) {
  _sll_pprint(list, sln_pprint);
}