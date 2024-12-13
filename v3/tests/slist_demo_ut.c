#include "slist.h"

#include <stdio.h>

SDECL_IMPL(slist, int)

void print_lst(struct slist *lst) {
  printf("size = %d\n", lst->size);
  for (struct slist_node *n = lst->first; n; n = n->next) {
    printf("%d ", n->value);
  }
  printf("\n");
}

int main() {
  struct slist *lst = slist();
  slist_append(lst, 1);
  slist_append(lst, 3);
  slist_append(lst, 5);
  slist_prepend(lst, 2);
  slist_prepend(lst, 6);
  print_lst(lst);
  slist_dfirst(lst);
  slist_dfirst(lst);
  print_lst(lst);
  slist_del(lst);
}