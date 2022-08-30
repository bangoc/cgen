#include "dab/spec/d2w.h"

int d2w_push_with_index(p2w_t h, long idx, double elem) {
  return p2w_push_with_index(h, idx, gtype_value(d, elem), gtype_cmp_d);
}

double d2w_max(const p2w_t h) {
  return p2w_max(h).d;
}

double d2w_get(const p2w_t h, long idx) {
  return p2w_get(h, idx).d;
}

double d2w_delete_max(p2w_t h) {
  return p2w_delete_max(h, gtype_cmp_d).d;
}

double d2w_deactivate_max(p2w_t h) {
  return p2w_deactivate_max(h, gtype_cmp_d).d;
}

double d2w_delete_max_index(p2w_t h, long *idx) {
  return p2w_delete_max_index(h, idx, gtype_cmp_d).d;
}

int d2w_modify(p2w_t h, long idx, double elem) {
  return p2w_modify(h, idx, gtype_value(d, elem), gtype_cmp_d);
}
