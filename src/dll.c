/*
  (C) Nguyen Ba Ngoc, 2021
*/

#include "dll.h"

#include <stdio.h>
#include <stdlib.h>

dll_node_t dll_create_node() {
  dll_node_t n = malloc(sizeof(struct dll_node_s));
  n->next = n->prev = NULL;
  return n;
}

void dll_free_node(dll_node_t node) {
  free(node);
}

dll_t dll_create_list() {
  dll_t list = malloc(sizeof(struct dll_s));
  list->front = list->back = NULL;
  list->fn = dll_free_node;
  return list;
}

void dll_free_list(dll_t list) {
  while (!dll_is_empty(list)) {
    dll_pop_front(list);
  }
  free(list);
}

void dll_push_back(dll_t list, dll_node_t nn) {
  if (list->back == NULL) {
    list->front = list->back = nn;
  } else {
    list->back->next = nn;
    nn->prev = list->back;
    list->back = nn;
  }
}

void dll_push_front(dll_t list, dll_node_t nn) {
  if (list->front == NULL) {
    list->front = list->back = nn;
  } else {
    list->front->prev = nn;
    nn->next = list->front;
    list->front = nn;
  }
}

void dll_pop_back(dll_t list) {
  if (dll_is_empty(list)) {
    return;
  }
  dll_node_t tmp = list->back;
  list->back = tmp->prev;
  if (list->back) {
    list->back->next = NULL;
  } else {
    list->front = NULL;
  }
  list->fn(tmp);
}

void dll_pop_front(dll_t list) {
  if (dll_is_empty(list)) {
    return;
  }
  dll_node_t tmp = list->front;
  list->front = tmp->next;
  if (list->front) {
    list->front->prev = NULL;
  } else {
    list->back = NULL;
  }
  list->fn(tmp);
}

dll_node_t dll_front(dll_t list) {
  return list->front;
}

dll_node_t dll_back(dll_t list) {
  return list->back;
}

/* insert nn after pos in list. push_back if pos == NULL */
dll_node_t dll_inserta(dll_t list, dll_node_t pos, dll_node_t nn) {
  if (!pos) {
    dll_push_back(list, nn);
    return nn;
  }

  dll_node_t tmp = pos->next;
  pos->next = nn;
  nn->prev = pos;
  nn->next = tmp;
  if (tmp) {
    tmp->prev = nn;
  } else {
    list->back = nn;
  }
  return nn;
}

/* insert nn before pos in list. push_front is pos == NULL */
dll_node_t dll_insertb(dll_t list, dll_node_t pos, dll_node_t nn) {
  if (!pos) {
    dll_push_front(list, nn);
    return nn;
  }

  dll_node_t tmp = pos->prev;
  pos->prev = nn;
  nn->next = pos;
  nn->prev = tmp;
  if (tmp) {
    tmp->next = nn;
  } else {
    list->front = nn;
  }
  return nn;
}

int dll_is_empty(dll_t list) {
  return list->front == NULL && list->back == NULL;
}

long dll_length(dll_t list) {
  long len = 0;
  dll_node_t n = dll_front(list);
  while (n) {
    ++len;
    n = n->next;
  }
  return len;
}

void dll_erase(dll_t list, dll_node_t pos) {
  if (pos == list->front) {
    dll_pop_front(list);
    return;
  }
  if (pos == list->back) {
    dll_pop_back(list);
    return;
  }

  // front < pos < back
  dll_node_t p1 = pos->prev,
             p2 = pos->next;
  p1->next = p2;
  p2->prev = p1;
  list->fn(pos);
}

void dll_clear(dll_t list) {
  while (!dll_is_empty(list)) {
    dll_pop_front(list);
  }
}

void dll_pprint_node(dll_node_t node) {
  printf("[%p]", node);
}

static void _dll_pprint_list(dll_t list, void (*ppn)()) {
  printf("NULL <= ");
  int first = 1;
  for (dll_node_t cur = list->front; cur != NULL; cur = cur->next) {
    if (first) {
      first = 0;
    } else {
      printf(" <==> ");
    }
    ppn(cur);
  }
  printf(" => NULL\n");
}

void dll_pprint_list(dll_t list) {
  _dll_pprint_list(list, dll_pprint_node);
}

/* Giao diện cho gtype */

dll_node_t dll_create_node_g(gtype value) {
  dll_node_g_t nn = malloc(sizeof(struct dll_node_g_s));
  nn->base.prev = nn->base.next = NULL;
  nn->value = value;
  return to_dll(nn);
}

void dll_push_back_g(dll_t list, gtype value) {
  dll_push_back(list, dll_create_node_g(value));
}

void dll_push_front_g(dll_t list, gtype value) {
  dll_push_front(list, dll_create_node_g(value));
}

gtype dll_pop_front_g(dll_t list) {
  gtype tmp = dll_front_g(list);
  dll_pop_front(list);
  return tmp;
}

gtype dll_pop_back_g(dll_t list) {
  gtype tmp = dll_back_g(list);
  dll_pop_back(list);
  return tmp;
}

gtype dll_front_g(dll_t list) {
  return dll_node_g_value(list->front);
}

gtype dll_back_g(dll_t list) {
  return dll_node_g_value(list->back);
}

dll_node_t dll_inserta_g(dll_t list, dll_node_t pos, gtype value) {
  dll_node_t nn = dll_create_node_g(value);
  dll_inserta(list, pos, nn);
  return nn;
}

dll_node_t dll_insertb_g(dll_t list, dll_node_t pos, gtype value) {
  dll_node_t nn = dll_create_node_g(value);
  dll_insertb(list, pos, nn);
  return nn;
}

/* Giao diện cho kiểu int */

dll_node_t dll_create_node_i(int value) {
  dll_node_i_t n = malloc(sizeof(struct dll_node_i_s));
  n->base.prev = n->base.next = NULL;
  n->value = value;
  return (dll_node_t)n;
}

void dll_push_back_i(dll_t list, int value) {
  dll_node_t nn = dll_create_node_i(value);
  dll_push_back(list, nn);
}

void dll_push_front_i(dll_t list, int value) {
  dll_node_t nn = dll_create_node_i(value);
  dll_push_front(list, nn);
}

int dll_pop_back_i(dll_t list) {
  int value = dll_back_i(list);
  dll_pop_back(list);
  return value;
}

int dll_pop_front_i(dll_t list) {
  int value = dll_front_i(list);
  dll_pop_front(list);
  return value;
}

int dll_front_i(dll_t list) {
  return dll_node_i_value(dll_front(list));
}

int dll_back_i(dll_t list) {
  return dll_node_i_value(dll_back(list));
}

dll_node_t dll_inserta_i(dll_t list, dll_node_t pos, int value) {
  return dll_inserta(list, pos, dll_create_node_i(value));
}

dll_node_t dll_insertb_i(dll_t list, dll_node_t pos, int value) {
  return dll_insertb(list, pos, dll_create_node_i(value));
}

void dll_pprint_node_i(dll_node_t node) {
  printf("[%d]", dll_node_i_value(node));
}

void dll_pprint_list_i(dll_t list) {
  _dll_pprint_list(list, dll_pprint_node_i);
}
