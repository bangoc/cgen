#include "slist.h"

#include <stdio.h>

SLIST_DECL_IMPL(ilist, int)

int main() {
  struct ilist *lst = ilist();
  ilist_ins(lst, 0, 3);
  ilist_ins(lst, 1, 5);
  ilist_ins(lst, 1, 2);
  for (struct ilist_node *n = lst->first; n; n = n->next) {
    printf(" %d", n->value);
  }
  if (lst->size != 3) {
    printf("Size = %d error\n", lst->size);
    return 1;
  }
  int a[] = {3, 2, 5};
  for (int i = 0; i < lst->size; ++i) {
    if (ilist_at(lst, i)->value != a[i]) {
      printf("Error at %d\n", i);
      return 1;
    }
  }
  ilist_del(lst, 1);
  printf("\nAfter delete index 1\n");
  for (struct ilist_node *n = lst->first; n; n = n->next) {
    printf(" %d", n->value);
  }
  if (lst->size != 2) {
    printf("Size = %d error\n", lst->size);
    return 1;
  }
  ilist_insa(lst, lst->first, 6);
  ilist_insa(lst, lst->last, 8);
  ilist_insa(lst, lst->last, 10);
  int b[] = {3, 6, 5, 8, 10};
  for (int i = 0; i < lst->size; ++i) {
    if (ilist_at(lst, i)->value != b[i]) {
      printf("Error at %d\n", i);
      return 1;
    }
  }
  printf("Test ok\n");
  ilist_free(lst);
}