#ifndef TESTS_RB_RBI_HELPER_H_
#define TESTS_RB_RBI_HELPER_H_

struct match_args {
  int *arr;
  int n;
  int i;
  int ok;
};

static int match_callback(bn_node_t nd, struct match_args *u) {
  int value = rbi_value(nd);
  if (u->i < u->n && u->arr[u->i] == value) {
    ++(u->i);
    return 0;
  }
  u->ok = 0;
  return 1;
}

int lnr_match(bn_tree_t t, int *arr, int n) {
  struct match_args args = {arr, n, 0, 1};
  bn_inorder_lnr_foreach(t, match_callback, &args);
  return args.ok;
}

#endif  // TESTS_RB_RBI_HELPER_H_