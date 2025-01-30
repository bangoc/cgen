#include "bst.h"
#include "tnav.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

BST_DECL_IMPL(bst, 256, int)
TNAV_DECL_IMPL(bst)

const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int n = sizeof(letters) - 1;

char *gens() {
  static char buff[11];
  int len = rand() % 10 + 1;
  for (int i = 0; i < len; ++i) {
    buff[i] = letters[rand() % n];
  }
  buff[len] = 0;
  return buff;
}

void nprint(struct bst_node *n, void *u) {
  printf(" (%s, %d)", n->key, n->value);
}

int main() {
  srand(time(NULL));
  struct bst *t = bst();
  for (int i = 0; i < 100000; ++i) {
    struct bst_node *n = bst_put(t, gens(), rand());
    if (n) {
      printf("Trùng khóa: %s\n", n->key);
    }
  }
  struct bst_node *n = bst_first_lnr(t);
  const char *key = n->key;
  for (n = bst_next_lnr(n); n; n = bst_next_lnr(n)) {
    if (strcmp(key, n->key) >= 0) {
      printf("Not a binary search tree");
      return 1;
    }
    key = n->key;
  }
  printf("Valid tree!\n");
  for (int i = 0; i < 1000; ++i) {
    struct bst_node *n = bst_get(t, gens());
    if (n) {
      printf("Found random key: %s\n", n->key);
    }
  }
  for (int i = 0; i < 1000; ++i) {
    const char *key = gens();
    if (bst_rem(t, gens())) {
      printf("Removed random key: %s\n", key);
    }
  }
  n = bst_first_lnr(t);
  key = n->key;
  for (n = bst_next_lnr(n); n; n = bst_next_lnr(n)) {
    if (strcmp(key, n->key) >= 0) {
      printf("Not a binary search tree");
      return 1;
    }
    key = n->key;
  }
  printf("Valid tree!\n");
  bst_trav(t->root, nprint, NULL, LEFT, NODE, RIGHT);
  printf("\n");
  bst_free(t);
}