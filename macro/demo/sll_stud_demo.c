#include "slist.h"

#include <stdio.h>
#include <string.h>

struct stud {
  char name[32];
};

SLIST_DECL_IMPL(sll, struct stud)

#define sequal(s1, s2) (strcmp(s1, s2) == 0)

int main() {
  struct sll *q = sll();
  char cmd[10];
  struct stud sv;
  while (scanf("%s", cmd) == 1) {
    if (sequal(cmd, "enq")) {
      scanf("%s", sv.name);
      sll_enq(q, sv);
    } else if (sequal(cmd, "fetch")) {
      printf("%s\n", sll_peek(q)->name);
      sll_deq(q);
    } else if (sequal(cmd, "len")) {
      printf("%d\n", q->size);
    }
  }
  sll_free(q);
}