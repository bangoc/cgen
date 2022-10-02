/* (C) Nguyen Ba Ngoc 2021 */

#include "list/sll.h"

#include <stdlib.h>
#include <stdio.h>

struct slnode *sll_create_node() {
  return calloc(1, sizeof(struct slnode));
}

struct sllist *sll_create_list() {
  return calloc(1, sizeof(struct sllist));
}

void __sll_push_back(struct sllist *list, struct slnode *node) {
  node->next = NULL;
  if (list->front == NULL) {
    list->front = list->back = node;
  } else {
    list->back->next = node;
    list->back = node;
  }
  ++list->length;
}

void __sll_push_front(struct sllist *list, struct slnode *node) {
  if (list->front == NULL) {
    list->front = list->back = node;
    node->next = NULL;
  } else {
    node->next = list->front;
    list->front = node;
  }
  ++list->length;
}

void __sll_inserta(struct sllist *list, struct slnode *pos, struct slnode *nn) {
  if (!pos) {
    __sll_push_back(list, nn);
    return;
  }

  struct slnode *tmp = pos->next;
  pos->next = nn;
  nn->next = tmp;
  if (!tmp) {
    list->back = nn;
  }
  ++list->length;
}

void __sll_pop_front(struct sllist *list) {
  if (sll_is_empty(list)) {
    return;
  }
  struct slnode *tmp = list->front;
  list->front = list->front->next;
  if (list->front == NULL) {
    list->back = NULL;
  }
  free(tmp);
  --list->length;
}

void sll_node_print_address(struct slnode *node) {
  printf("[%p]", node);
}

void sll_pprint(struct sllist *list, sll_node_print_t npp) {
  sll_traverse(cur, list) {
    npp(cur);
    printf(" ");
  }
  printf("\n");
}