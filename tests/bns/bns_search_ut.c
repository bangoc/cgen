#include "tests/base/utils.h"
#include "base/bns.h"

int *make_pointer_i(int value) {
  int *p = malloc(sizeof(int));
  *p = value;
  return p;
}

struct bns_node {
  struct bn_node bnt;
  int value;
};

#define to_bns(n) ((struct bns_node *)n)

int bns_compare(bn_node_t n1, bn_node_t n2) {
  int value1 = to_bns(n1)->value;
  int value2 = to_bns(n2)->value;
  return value1 - value2;
}

int main() {
  struct bns_node n1 = {.value = 1};
  struct bns_node n2 = {.value = 2};
  struct bns_node n3 = {.value = 3};
  struct bns_node n4 = {.value = 4};
  struct bns_node n5 = {.value = 5};
  struct bns_node n6 = {.value = 6};
  struct bns_node n_1 = {.value = -1};

  n2.bnt.left = &n1.bnt;
  n1.bnt.top = &n2.bnt;
  n2.bnt.right = &n3.bnt;
  n3.bnt.top = &n2.bnt;
  n3.bnt.right = &n5.bnt;
  n5.bnt.top = &n3.bnt;
  n5.bnt.left = &n4.bnt;
  n4.bnt.top = &n5.bnt;
  bn_tree_t t = bn_create_tree(&n2.bnt);
  /*
          2
        1   3
              5
            4
  */
  bns_search_inline(n, t, &n1.bnt, bns_compare,
    CHECK_MSG(n == &n1.bnt, "Failed search 1"));
  bns_search_inline(n, t, &n2.bnt, bns_compare,
    CHECK_MSG(n == &n2.bnt, "Failed search 2"));
  bns_search_inline(n, t, &n3.bnt, bns_compare,
    CHECK_MSG(n == &n3.bnt, "Failed search 3"));
  bns_search_inline(n, t, &n4.bnt, bns_compare,
    CHECK_MSG(n == &n4.bnt, "Failed search 4"));
  bns_search_inline(n, t, &n5.bnt, bns_compare,
    CHECK_MSG(n == &n5.bnt, "Failed search 5"));
  bns_search_inline(n, t, &n6.bnt, bns_compare,
    CHECK_MSG(n == NULL_PTR, "Failed search 6"));
  bns_search_inline(n, t, &n_1.bnt, bns_compare,
    CHECK_MSG(n == NULL_PTR, "Failed search -1"));
  free(t);
  TEST_OK();
}
