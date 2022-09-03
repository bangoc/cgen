#ifndef TESTS_DLL_HELPER_H_
#define TESTS_DLL_HELPER_H_

/*
  (C) Nguyen Ba Ngoc, 2021
*/

#include "all.h"

#include <stdio.h>

static int dll_sequence(dll_t list, dln_t *a, int n) {
  if (dll_length(list) != n) {
    return 0;
  }

  dln_t p = list->front;
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
  if (dll_length(list) != n) {
    return 0;
  }
  dln_t p = list->front;
  for (int i = 0; i < n; ++i) {
    if (idn_value(p) != a[i]) {
      return 0;
    }
    p = p->next;
  }
  if (p != NULL) {
    return 0;
  }
  p = list->back;
  for (int i = n - 1; i >= 0; --i) {
    if (idn_value(p) != a[i]) {
      return 0;
    }
    p = p->prev;
  }
  if (p != NULL) {
    return 0;
  }
  return 1;
}

static int gdl_sequence_g(gdl_t list, gtype *a, int n, gtype_cmp_t cmp) {
  if (gdl_size(list) != n) {
    return 0;
  }
  gtype *p = list->front;
  for (int i = 0; i < n; ++i) {
    if (cmp(gdn_value(p), a[i]) != 0) {
      return 0;
    }
    p = gdn_next(p);
  }
  if (p != NULL) {
    return 0;
  }
  p = gdl_back(list);
  for (int i = n - 1; i >= 0; --i) {
    if (cmp(gdn_value(p), a[i]) != 0) {
      return 0;
    }
    p = gdn_prev(p);
  }
  if (p != NULL) {
    return 0;
  }
  return 1;
}

#endif  // TESTS_DLL_HELPER_H_
