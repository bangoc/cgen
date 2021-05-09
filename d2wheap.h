/*
  (C) 2021 Nguyen Ba Ngoc (bangoc)
*/

#ifndef D2WHEAP_H_
#define D2WHEAP_H_

#include "gtp2wheap.h"

// ========== Khai báo hàm ===============

static int d2w_push_with_index(p2wheap_t h, long idx, double elem);
static double d2w_max(const p2wheap_t h);
static double d2w_get(const p2wheap_t h, long idx);
static double d2w_delete_max(p2wheap_t h);
static double d2w_deactivate_max(p2wheap_t h);
static double d2w_delete_max_index(p2wheap_t h, long *idx);
static int d2w_modify(p2wheap_t h, long idx, double elem);


// ========== Macro viết nhanh ===========

static int d2w_push_with_index(p2wheap_t h, long idx, double elem) {
  return p2w_push_with_index(h, idx, gtype_value(d, elem), gtype_cmp_d);
}

static double d2w_max(const p2wheap_t h) {
  return p2w_max(h).d;
}

static double d2w_get(const p2wheap_t h, long idx) {
  return p2w_get(h, idx).d;
}

static double d2w_delete_max(p2wheap_t h) {
  return p2w_delete_max(h, gtype_cmp_d).d;
}

static double d2w_deactivate_max(p2wheap_t h) {
  return p2w_deactivate_max(h, gtype_cmp_d).d;
}

static double d2w_delete_max_index(p2wheap_t h, long *idx) {
  return p2w_delete_max_index(h, idx, gtype_cmp_d).d;
}

static int d2w_modify(p2wheap_t h, long idx, double elem) {
  return p2w_modify(h, idx, gtype_value(d, elem), gtype_cmp_d);
}

// ========== Định nghĩa hàm =============



#endif  // D2WHEAP_H_