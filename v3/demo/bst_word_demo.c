#include "bst.h"

#include <stdio.h>
#include <string.h>

BST_DECL_IMPL(bst, 32, int)

int main() {
  struct bst *t = bst();
  char cmd[32], word[32];
  while (scanf("%s", cmd) == 1) {
    if (strcmp(cmd, "print") == 0) {
      printf("Traverse: \n");
      for (struct bst_node *n = bst_first(t); n; n = bst_next(n)) {
        printf("%s: %d\n", n->key, n->value);
      }
      continue;
    }
    scanf("%s", word);
    if (strcmp(cmd, "insert") == 0) {
      struct bst_node *n = bst_put(t, word, 1);
      if (n) {
        ++n->value;
        printf("freq(%s) updated = %d\n", word, n->value);
      } else {
        printf("Inserted %s\n", word);
      }
    } else if (strcmp(cmd, "freq") == 0) {
      struct bst_node *n = bst_search(t, word);
      printf("freq(%s) = %d\n", word, n? n->value: 0);
    } else if (strcmp(cmd, "rem") == 0) {
      if (bst_rem(t, word)) {
        printf("Deleted %s\n", word);
      }
    }
  }
  bst_del(t);
}