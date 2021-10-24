#ifndef TESTS_DLL_HELPER_H_
#define TESTS_DLL_HELPER_H_

/*
  (C) Nguyen Ba Ngoc, 2021
*/

#include "dll.h"

#include <stdio.h>

static int dll_sequence(dll_t list, dll_node_t *a, int n) {
  dll_node_t p = list->front;
  for (int i = 0; i < n; ++i) {
    if (p != a[i]) {
      return 0;
    }
    p = p->next;
  }
  if (p != NULL) {
    return 0;
  }
  p = list->back;
  for (int i = n - 1; i >= 0; --i) {
    if (p != a[i]) {
      return 0;
    }
    p = p->prev;
  }
  if (p != NULL) {
    return 0;
  }
  return 1;
}

static int dll_sequence_i(dll_t list, int *a, int n) {
  dll_node_t p = list->front;
  for (int i = 0; i < n; ++i) {
    if (node_i_value(p) != a[i]) {
      return 0;
    }
    p = p->next;
  }
  if (p != NULL) {
    return 0;
  }
  p = list->back;
  for (int i = n - 1; i >= 0; --i) {
    if (node_i_value(p) != a[i]) {
      return 0;
    }
    p = p->prev;
  }
  if (p != NULL) {
    return 0;
  }
  return 1;
}

#endif  // TESTS_DLL_HELPER_H_