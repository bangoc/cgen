#ifndef TESTS_RB_RBI_HELPER_H_
#define TESTS_RB_RBI_HELPER_H_

#include "tests/rb/rbi.h"

struct match_args {
  void *arr;
  int n;
  int i;
  int ok;
};

struct attrib {
  int value;
  int color;
};

static int match_value_callback(struct bnn *nd, struct match_args *u) {
  int value = rbi_value(nd);
  int tmp = ((int*)u->arr)[u->i];
  if (u->i < u->n && tmp == value) {
    ++(u->i);
    return 0;
  }
  u->ok = 0;
  return 1;
}

static int match_color_callback(struct bnn *nd, struct match_args *u) {
  int color = (int)rb_color(nd);
  int tmp = ((int*)u->arr)[u->i];
  if (u->i < u->n && tmp == color) {
    ++(u->i);
    return 0;
  }
  u->ok = 0;
  return 1;
}

static int match_callback(struct bnn *nd, struct match_args *u) {
  int value = rbi_value(nd);
  int color = (int)rb_color(nd);
  struct attrib *p = ((struct attrib*)u->arr) + u->i;
  if (u->i < u->n && p->value == value && p->color == color) {
    ++(u->i);
    return 0;
  }
  u->ok = 0;
  return 1;
}

static int lnr_match_value(struct bnt *t, int *arr, int n) {
  struct match_args args = {arr, n, 0, 1};
  bn_foreach_lnr(t, match_value_callback, &args);
  return args.ok;
}

static int lnr_match_color(struct bnt *t, int *arr, int n) {
  struct match_args args = {arr, n, 0, 1};
  bn_foreach_lnr(t, match_color_callback, &args);
  return args.ok;
}

static int lnr_match_attrib(struct bnt *t, struct attrib *arr, int n) {
  struct match_args args = {arr, n, 0, 1};
  bn_foreach_lnr(t, match_callback, &args);
  return args.ok;
}

#endif  // TESTS_RB_RBI_HELPER_H_
