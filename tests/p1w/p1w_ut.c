#include "p1w.h"

#include "tests/base/utils.h"

int t1() {
  p1w_t q = p1w_create(PRIORITY_MAX, gtype_cmp_i);
  p1w_enqueue(q, gtype_i(10));
  p1w_enqueue(q, gtype_i(30));
  p1w_enqueue(q, gtype_i(20));
  p1w_enqueue(q, gtype_i(50));
  p1w_enqueue(q, gtype_i(60));
  CHECK_ECHO(p1w_dequeue(q).i == 60);
  CHECK_ECHO(p1w_dequeue(q).i == 50);
  CHECK_ECHO(p1w_dequeue(q).i == 30);
  CHECK_ECHO(p1w_peek(q).i == 20);
  CHECK_ECHO(p1w_dequeue(q).i == 20);
  CHECK_ECHO(p1w_dequeue(q).i == 10);
  CHECK_ECHO(p1w_is_empty(q));
  p1w_free(q);
}

int t2() {
  p1w_t q = p1w_create(PRIORITY_MIN, gtype_cmp_i);
  p1w_enqueue(q, gtype_i(10));
  p1w_enqueue(q, gtype_i(30));
  p1w_enqueue(q, gtype_i(20));
  p1w_enqueue(q, gtype_i(60));
  p1w_enqueue(q, gtype_i(50));
  CHECK_ECHO(p1w_dequeue(q).i == 10);
  CHECK_ECHO(p1w_dequeue(q).i == 20);
  CHECK_ECHO(p1w_peek(q).i == 30);
  CHECK_ECHO(p1w_dequeue(q).i == 30);
  CHECK_ECHO(p1w_dequeue(q).i == 50);
  CHECK_ECHO(p1w_dequeue(q).i == 60);
  CHECK_ECHO(p1w_is_empty(q));
  p1w_free(q);
}

int main() {
  CHECK_ECHO(t1() == 0);
  CHECK_ECHO(t2() == 0);
  TEST_OK();
}