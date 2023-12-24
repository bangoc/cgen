#include "cgen.h"
#include "tests/utils.h"
SDECL_IMPL(list, char *, s);
void demo_stack() {
  printf("Demo stack: ==== \n");
  struct list *stk = list();
  spush(stk, "aaaaa");
  spush(stk, "bbbbbbbb");
  spush(stk, "ccccccccccc");
  while (!sempty(stk)) {
    printf("%s\n", *stop(stk));
    spop(stk);
  }
  sfree(stk);
}
void demo_queue() {
  printf("Demo queue: =======\n");
  struct list *q = list();
  senque(q, "aaaaaaaaaaa");
  senque(q, "bbbbbbb");
  senque(q, "ccccccccccccccccc");
  while (!sempty(q)) {
    printf("%ld: %s\n", q->size, *speek(q));
    sdeque(q);
  }
  sfree(q);
}
int main() {
  demo_stack();
  demo_queue();
  TEST_OK();
}