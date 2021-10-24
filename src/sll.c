#include "sll.h"

sll_t sll_create() {
  sll_t l = calloc(1, sizeof(struct sll_s));
  return l;
}

sll_t sll_push_back(sll_t list, sll_node_t node) {
  node->next = NULL;
  if (list->front == NULL) {
    list->front = list->back = node;
  } else {
    list->back->next = node;
    list->back = node;
  }
  list->size++;
  return list;
}

sll_t sll_push_front(sll_t list, sll_node_t node) {
  if (list->front == NULL) {
    list->front = list->back = node;
    node->next = NULL;
  } else {
    node->next = list->front;
    list->front = node;
  }
  ++list->size;
  return list;
}

sll_node_t sll_pop_front(sll_t list) {
  if (list->size == 0) {
    return NULL;
  }
  sll_node_t node = list->front;
  list->front = list->front->next;
  --list->size;
  if (list->size == 0) {
    list->back = NULL;
  }
  return node;
}

bool sll_empty(sll_t list) {
  return list->size == 0;
}

/* Triển khai giao diện gtype */

gsl_node_t gsl_make_node(gtype value) {
  gsl_node_t node = malloc(sizeof(struct gsl_node_s));
  node->val = value;
  return node;
}

sll_t gsl_push_back(sll_t list, gsl_node_t val) {
  return sll_push_back(list, &val->node);
}

sll_t gsl_push_front(sll_t list, gsl_node_t val) {
  return sll_push_front(list, &val->node);
}

gsl_node_t gsl_pop_front(sll_t list) {
  sll_node_t node = sll_pop_front(list);
  return to_gsl(node);
}

/* Triển khai giao diện stack số nguyên */
sll_t ist_push(sll_t list, long value) {
  return gsl_push_front(list, gsl_make_node((gtype){.i = value}));
}

long ist_pop(sll_t list) {
  gsl_node_t node = gsl_pop_front(list);
  if (node) {
    long value = node->val.i;
    free(node);
    return value;
  }
  return INVALID_VALUE.i;
}

long ist_top(sll_t list) {
  if (list && list->front) {
    gsl_node_value(list).i;
  }
  return INVALID_VALUE.i;
}

/* Triển khai giao diện queue số nguyên */
sll_t iqu_enqueue(sll_t list, long value) {
  return gsl_push_back(list, gsl_make_node((gtype){.i = value}));
}

long iqu_dequeue(sll_t list) {
  gsl_node_t node = gsl_pop_front(list);
  if (node) {
    long value = node->val.i;
    free(node);
    return value;
  }
  return INVALID_VALUE.i;
}

long iqu_peek(sll_t list) {
  if (list && list->front) {
    gsl_node_value(list).i;
  }
  return INVALID_VALUE.i;
}