#include "slist.h"

#include <stdio.h>

SLIST_DECL_IMPL(ilist, int)

int main() {
  struct ilist *lst = ilist();
  ilist_ins(lst, 3, 0);
  ilist_ins(lst, 5, 1);
  ilist_ins(lst, 2, 1);
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
  int b[] = {3, 5};
  for (int i = 0; i < lst->size; ++i) {
    if (ilist_at(lst, i)->value != b[i]) {
      printf("Error at %d\n", i);
      return 1;
    }
  }
  printf("Test ok\n");
  ilist_free(lst);
}