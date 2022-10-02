/* (C) Nguyen Ba Ngoc 2021 */

#include "list/dll.h"

#include <stdio.h>
#include <stdlib.h>

struct dlnode *dll_create_node() {
  return calloc(1, sizeof(struct dlnode));
}

struct dllist *dll_create_list() {
  return calloc(1, sizeof(struct dllist));
}

void __dll_push_back(struct dllist *list, struct dlnode *nn) {
  if (list->back == NULL) {
    list->front = list->back = nn;
  } else {
    list->back->next = nn;
    nn->prev = list->back;
    list->back = nn;
  }
  ++list->length;
}

void __dll_push_front(struct dllist *list, struct dlnode *nn) {
  if (list->front == NULL) {
    list->front = list->back = nn;
  } else {
    list->front->prev = nn;
    nn->next = list->front;
    list->front = nn;
  }
  ++list->length;
}

void __dll_pop_back(struct dllist *list) {
  if (dll_is_empty(list)) {
    return;
  }
  struct dlnode *tmp = list->back;
  list->back = tmp->prev;
  if (list->back) {
    list->back->next = NULL;
  } else {
    list->front = NULL;
  }
  free(tmp);
  --list->length;
}

void __dll_pop_front(struct dllist *list) {
  if (dll_is_empty(list)) {
    return;
  }
  struct dlnode *tmp = list->front;
  list->front = tmp->next;
  if (list->front) {
    list->front->prev = NULL;
  } else {
    list->back = NULL;
  }
  free(tmp);
  --list->length;
}

/* insert nn after pos in list. push_back if pos == NULL */
void __dll_inserta(struct dllist *list, struct dlnode *pos, struct dlnode *nn) {
  if (!pos) {
    __dll_push_back(list, nn);
    return;
  }

  struct dlnode *tmp = pos->next;
  pos->next = nn;
  nn->prev = pos;
  nn->next = tmp;
  if (tmp) {
    tmp->prev = nn;
  } else {
    list->back = nn;
  }
  ++list->length;
}

/* insert nn before pos in list. push_front is pos == NULL */
void __dll_insertb(struct dllist *list, struct dlnode *pos, struct dlnode *nn) {
  if (!pos) {
    __dll_push_front(list, nn);
    return;
  }

  struct dlnode *tmp = pos->prev;
  pos->prev = nn;
  nn->next = pos;
  nn->prev = tmp;
  if (tmp) {
    tmp->next = nn;
  } else {
    list->front = nn;
  }
  ++list->length;
}

void __dll_erase(struct dllist *list, struct dlnode *pos) {
  if (pos == list->front) {
    __dll_pop_front(list);
    return;
  }
  if (pos == list->back) {
    __dll_pop_back(list);
    return;
  }

  struct dlnode *p1 = pos->prev,
             *p2 = pos->next;
  p1->next = p2;
  p2->prev = p1;
  free(pos);
  --list->length;
}

void dll_node_print_address(struct dlnode *node) {
  printf("[%p]", node);
}

void dll_pprint(struct dllist *list, dll_node_print_t npp) {
  dll_traverse(cur, list) {
    npp(cur);
    printf(" ");
  }
  printf("\n");
}
