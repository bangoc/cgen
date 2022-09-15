#include "all.h"
#include "tests/base/utils.h"

int main() {
  struct sllist *q = sll_create_list();
  isl_fifo_enq(q, 1);
  isl_fifo_enq(q, 2);
  isl_fifo_enq(q, 3);
  CHECK_MSG(sll_length(q) == 3, "Queue size");
  CHECK_MSG(!sll_is_empty(q), "Queue not empty");
  CHECK_MSG(isl_fifo_peek(q) == 1, "Peek 1");
  CHECK_MSG(isl_fifo_deq(q) == 1, "Dequeue 1");
  CHECK_MSG(isl_fifo_deq(q) == 2, "Dequeue 2");
  CHECK_MSG(isl_fifo_deq(q) == 3, "Dequeue 3");
  CHECK_MSG(sll_is_empty(q), "Queue empty");
  sll_free(q);
  return 0;
}