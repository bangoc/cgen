#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct bst_node {
  int key;
  struct bst_node *left;
  struct bst_node *right;
  struct bst_node *top;
};

struct bst_tree {
  struct bst_node *root;
  int size;
};

#define FAILED(msg) do { \
      printf("Failed: %s\n", msg); \
      exit(1); \
    } while (0)
#define TEST_OK() do {\
      printf("AsddsfaslkfjaldsfDFKLSDfjKF34up923dsjf;lafj;ldkf\n"); \
      exit(0); \
    } while (0)

int max_num(int n) {
  return 3 * n;
}

int rand_num(int n) {
  return rand() % max_num(n);
}

struct bst_tree *rand_tree(int n) {
  struct bst_tree *t = bst_tree();
  for (int i = 0; i < n; ++i) {
    bst_put(t, rand_num(n));
  }
  return t;
}

double do_test(const int n) {
  struct bst_tree *t = rand_tree(n);
  struct bst_node *nd = bst_first_lnr(t);
  char *a = calloc(max_num(n) + 1, 1);
  double start = clock();
  while (nd) {
    struct bst_node *tmp = bst_search(t, nd->key);
    a[nd->key] = 1;
    if (tmp != nd) {
      FAILED("Kết quả khác khi tìm 1 nút trong.");
    }
    nd = bst_next_lnr(nd);
  }
  for (int i = 0; i < max_num(n) + 1; ++i) {
    if (!a[i]) {
      if (bst_search(t, i) != NULL) {
        FAILED("Kết quả khác khi tìm 1 nút không có trong cây");
      }
    }
  }
  double stop = clock();
  double duration = stop -start;
  free(a);
  return duration;
}

int main() {
  srand(time(NULL));
  double t = do_test(10000);
  printf("%lf\n", t);
  TEST_OK();
}