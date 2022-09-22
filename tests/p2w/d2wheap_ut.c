/* (C) Nguyen Ba Ngoc 2021 */

#include "vec/spec/d2w.h"

#include "tests/base/utils.h"

int main() {
  struct p2ways *h = p2w_create(gtype_cmp_d);
  d2w_push_with_index(h, 0, 0);
  d2w_push_with_index(h, 1, 100.1);
  d2w_push_with_index(h, 2, 200.2);
  d2w_push_with_index(h, 3, 300.3);
  d2w_push_with_index(h, 5, 500.5);

  CHECK_MSG(p2w_check(h) == true, "Check max heap");

  CHECK_MSG(d2w_max(h) == 500.5, "Max 500.5");
  CHECK_MSG(d2w_get(h, 2) == 200.2, "Value at 2");
  CHECK_MSG(d2w_get(h, 1) == 100.1, "Value at 1");

  d2w_modify(h, 1, 10000.01);
  CHECK_MSG(d2w_max(h) == 10000.01, "Max 10000");
  CHECK_MSG(p2w_max_index(h) == 1, "Max 10000 index 1");

  CHECK_MSG(d2w_delete_max(h) == 10000.01, "Delete max 10000");
  CHECK_MSG(d2w_delete_max(h) == 500.5, "Delete max 500");
  CHECK_MSG(d2w_delete_max(h) == 300.3, "Delete max 300");
  CHECK_MSG(d2w_delete_max(h) == 200.2, "Delete max 200");
  CHECK_MSG(d2w_delete_max(h) == 0, "Delete max 0");
  p2w_free(h);
  return 0;
}