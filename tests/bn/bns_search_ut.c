#include "tests/base/utils.h"
#include "bns.h"

int *make_pointer_i(int value) {
  int *p = malloc(sizeof(int));
  *p = value;
  return p;
}

struct bns_node {
  struct bn_node bnt;
  int value;
};

int bns_compare(bn_node_t node, void *key) {
  int value1 = container_of(node, struct bns_node, bnt)->value;
  int value2 = *((int*)key);
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
  int v1 = 1, v2 = 2, v3 = 3, v4 = 4, v5 = 5, v6 = 6, v_1 = -1;
  CHECK_MSG(bns_search(t->root, &v1, bns_compare) == &n1.bnt, "Failed search 1");
  CHECK_MSG(bns_search(t->root, &v2, bns_compare) == &n2.bnt, "Failed search 2");
  CHECK_MSG(bns_search(t->root, &v3, bns_compare) == &n3.bnt, "Failed search 3");
  CHECK_MSG(bns_search(t->root, &v4, bns_compare) == &n4.bnt, "Failed search 4");
  CHECK_MSG(bns_search(t->root, &v5, bns_compare) == &n5.bnt, "Failed search 5");
  CHECK_MSG(bns_search(t->root, &v6, bns_compare) == NULL_PTR, "Failed search 6");
  CHECK_MSG(bns_search(t->root, &v_1, bns_compare) == NULL_PTR, "Failed search -1");
  return 0;
}