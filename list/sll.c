/* (C) Nguyen Ba Ngoc 2021 */

#include "list/sll.h"

#include <stdlib.h>
#include <stdio.h>

sln_t sll_create_node() {
  return calloc(sizeof(struct single_linked_node), 1);
}

sll_t sll_create_list() {
  return calloc(sizeof(struct single_linked_list), 1);
}

void sll_push_back(sll_t list, sln_t node) {
  node->next = NULL;
  if (list->front == NULL) {
    list->front = list->back = node;
  } else {
    list->back->next = node;
    list->back = node;
  }
  ++list->length;
}

void sll_push_front(sll_t list, sln_t node) {
  if (list->front == NULL) {
    list->front = list->back = node;
    node->next = NULL;
  } else {
    node->next = list->front;
    list->front = node;
  }
  ++list->length;
}

void sll_inserta(sll_t list, sln_t pos, sln_t nn) {
  if (!pos) {
    sll_push_back(list, nn);
    return;
  }

  dln_t tmp = pos->next;
  pos->next = nn;
  nn->next = tmp;
  if (!tmp) {
    list->back = nn;
  }
  ++list->length;
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
  free(tmp);
  --list->length;
}

void sll_node_print_address(sln_t node) {
  printf("[%p]", node);
}

void sll_pprint(sll_t list, sll_node_print_t npp) {
  sll_traverse(cur, list) {
    npp(cur);
    printf(" ");
  }
  printf("\n");
}