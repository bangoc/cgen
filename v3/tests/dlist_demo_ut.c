/* (C) Nguyễn Bá Ngọc 2025 */

#include "dlist.h"

#include <stdio.h>

DLIST_DECL_IMPL(dll, int)

int main() {
  struct dll *list = dll();
  dll_append(list, 3);
  dll_append(list, 5);
  dll_prepend(list, 1);
  for (struct dll_node *n = list->first; n; n = n->next) {
    printf(" %d", n->value);
  }
  printf("\n");
  for (struct dll_node *n = list->last; n; n = n->prev) {
    printf(" %d", n->value);
  }
  printf("\n");
  if (list->size != 3) {
    printf("size = %d - error\n", list->size);
    return 1;
  }
  dll_ins(list, 7, 3);
  dll_ins(list, 0, 0);
  int a[] = {0, 1, 3, 5, 7};
  if (list->size != 5) {
    printf("size = %d - error\n", list->size);
    return 1;
  }
  int i = 0;
  for (struct dll_node *n = list->first; n; n = n->next) {
    if (n->value != a[i++]) {
      printf("Value error at %d = %d\n", i, n->value);
      return 1;
    }
  }
  i = 4;
  for (struct dll_node *n = list->last; n; n = n->prev) {
    if (n->value != a[i--]) {
      printf("Value error at %d = %d\n", i, n->value);
      return 1;
    }
  }
  dll_insa(list, 7, list->first);
  dll_insb(list, 9, list->last);
  dll_insb(list, 11, list->last);

  for (struct dll_node *n = list->first; n; n = n->next) {
    printf(" %d", n->value);
  }
  printf("\n");

  // 0 7 1 3 5 9 11 7
  dll_dfirst(list);
  dll_dlast(list);
  dll_dnode(list, list->last);

  // 7 1 3 5 9
  dll_del(list, 1);
  dll_insb(list, 5, list->first);
  dll_insa(list, 15, list->last);

  int b[] = {5, 7, 3, 5, 9, 15};
  if (list->size != 6) {
    printf("Size = %d -- error\n", list->size);
    return 1;
  }
  i = 0;
  for (struct dll_node *n = list->first; n; n = n->next) {
    if (n->value != b[i++]) {
      printf("Value error at %d = %d\n", i, n->value);
      return 1;
    }
  }
  i = 5;
  for (struct dll_node *n = list->last; n; n = n->prev) {
    if (n->value != b[i--]) {
      printf("Value error at %d = %d\n", i, n->value);
      return 1;
    }
  }
  printf("Test Ok\n");
  dll_free(list);
}