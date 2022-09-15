/* (C) Nguyen Ba Ngoc 2021 */

#include "list/sll.h"

#include <stdlib.h>
#include <stdio.h>

struct sln *sll_create_node() {
  return calloc(sizeof(struct sln), 1);
}

struct sll *sll_create_list() {
  return calloc(sizeof(struct sll), 1);
}

void sll_push_back(struct sll *list, struct sln *node) {
  node->next = NULL;
  if (list->front == NULL) {
    list->front = list->back = node;
  } else {
    list->back->next = node;
    list->back = node;
  }
  ++list->length;
}

void sll_push_front(struct sll *list, struct sln *node) {
  if (list->front == NULL) {
    list->front = list->back = node;
    node->next = NULL;
  } else {
    node->next = list->front;
    list->front = node;
  }
  ++list->length;
}

void sll_inserta(struct sll *list, struct sln *pos, struct sln *nn) {
  if (!pos) {
    sll_push_back(list, nn);
    return;
  }

  struct dln *tmp = pos->next;
  pos->next = nn;
  nn->next = tmp;
  if (!tmp) {
    list->back = nn;
  }
  ++list->length;
}

void sll_pop_front(struct sll *list) {
  if (sll_is_empty(list)) {
    return;
  }
  struct sln *tmp = list->front;
  list->front = list->front->next;
  if (list->front == NULL) {
    list->back = NULL;
  }
  free(tmp);
  --list->length;
}

void sll_node_print_address(struct sln *node) {
  printf("[%p]", node);
}

void sll_pprint(struct sll *list, sll_node_print_t npp) {
  sll_traverse(cur, list) {
    npp(cur);
    printf(" ");
  }
  printf("\n");
}