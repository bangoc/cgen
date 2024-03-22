#include "bst-int.h"

#include <stdio.h>

int main() {
  struct bst_tree *t = bst_tree();
  int key;
  while (scanf("%d", &key) == 1) {
    if (key == -1) {
      break;
    }
    bst_put(t, key);
  }
  bst_pprint(t);
  bst_free(t);
}