#include "tmap.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TMAP_DECL_IMPL(rbt, char *, int)

void str_assign(char **des, const char *src) {
  *des = strdup(src);
}

int main() {
  struct rbt *t = rbt(strcmp);
  rbt_ak(t, str_assign);
  rbt_fk(t, free);
  char cmd[32], word[32];
  while (scanf("%s", cmd) == 1) {
    if (strcmp(cmd, "print") == 0) {
      printf("Traverse: \n");
      for (struct rbt_node *n = rbt_first_lnr(t); n; n = rbt_next_lnr(n)) {
        printf("%s: %d\n", n->key, n->value);
      }
      continue;
    }
    scanf("%s", word);
    if (strcmp(cmd, "insert") == 0) {
      struct rbt_node *n = rbt_put(t, word, 1);
      if (n) {
        ++n->value;
        printf("freq(%s) updated = %d\n", word, n->value);
      } else {
        printf("Inserted %s\n", word);
      }
    } else if (strcmp(cmd, "freq") == 0) {
      struct rbt_node *n = rbt_get(t, word);
      printf("freq(%s) = %d\n", word, n? n->value: 0);
    } else if (strcmp(cmd, "rem") == 0) {
      if (rbt_rem(t, word)) {
        printf("Deleted %s\n", word);
      }
    }
  }
  rbt_free(t);
}