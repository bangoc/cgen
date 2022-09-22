#include "vec/spec/d2w.h"

int d2w_push_with_index(struct p2ways *h, long idx, double elem) {
  return p2w_push_with_index(h, idx, gtype_value(d, elem));
}

double d2w_max(const struct p2ways *h) {
  return p2w_max(h).d;
}

double d2w_get(const struct p2ways *h, long idx) {
  return p2w_get(h, idx).d;
}

double d2w_delete_max(struct p2ways *h) {
  return p2w_delete_max(h).d;
}

double d2w_deactivate_max(struct p2ways *h) {
  return p2w_deactivate_max(h).d;
}

double d2w_delete_max_index(struct p2ways *h, long *idx) {
  return p2w_delete_max_index(h, idx).d;
}

int d2w_modify(struct p2ways *h, long idx, double elem) {
  return p2w_modify(h, idx, gtype_value(d, elem));
}
