#include "sll.h"
#include "tests/base/utils.h"

int main() {
  sll_t q = sll_create_list();
  sll_queue_enqueue_l(q, 1);
  sll_queue_enqueue_l(q, 2);
  sll_queue_enqueue_l(q, 3);
  CHECK_MSG(q->size == 3, "Queue size");
  CHECK_MSG(!sll_is_empty(q), "Queue not empty");
  CHECK_MSG(sll_queue_dequeue_l(q) == 1, "Dequeue 1");
  CHECK_MSG(sll_queue_dequeue_l(q) == 2, "Dequeue 2");
  CHECK_MSG(sll_queue_dequeue_l(q) == 3, "Dequeue 3");
  CHECK_MSG(sll_is_empty(q), "Queue empty");
  sll_free_list(q);
  return 0;
}