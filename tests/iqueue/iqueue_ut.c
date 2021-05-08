#include "iqueue.h"
#include "tests/base/utils.h"

int main() {
  list1_t q = list1_create();
  iqu_enqueue(q, 1);
  iqu_enqueue(q, 2);
  iqu_enqueue(q, 3);
  CHECK_MSG(q->size == 3, "Queue size");
  CHECK_MSG(list1_empty(q) == false, "Queue not empty");
  CHECK_MSG(iqu_dequeue(q) == 1, "Dequeue 1");
  CHECK_MSG(iqu_dequeue(q) == 2, "Dequeue 2");
  CHECK_MSG(iqu_dequeue(q) == 3, "Dequeue 3");
  CHECK_MSG(list1_empty(q) == true, "Queue empty");
  return 0;
}