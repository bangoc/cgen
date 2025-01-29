#include "bst.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

BST_DECL_IMPL(bst, 256, int)

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

int main() {
  srand(time(NULL));
  struct bst *t = bst();
  for (int i = 0; i < 100000; ++i) {
    struct bst_node *n = bst_put(t, gens(), rand());
    if (n) {
      printf("Trùng khóa: %s\n", n->key);
    }
  }
  struct bst_node *n = bst_first(t);
  const char *key = n->key;
  for (n = bst_next(n); n; n = bst_next(n)) {
    if (strcmp(key, n->key) >= 0) {
      printf("Not a binary search tree");
      return 1;
    }
    key = n->key;
  }
  printf("Valid tree!\n");
  for (int i = 0; i < 1000; ++i) {
    struct bst_node *n = bst_search(t, gens());
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
  n = bst_first(t);
  key = n->key;
  for (n = bst_next(n); n; n = bst_next(n)) {
    if (strcmp(key, n->key) >= 0) {
      printf("Not a binary search tree");
      return 1;
    }
    key = n->key;
  }
  printf("Valid tree!\n");
  bst_del(t);
}