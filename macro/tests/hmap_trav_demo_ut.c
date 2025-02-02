#include "hmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HMAP_DECL_IMPL(simap, char *, int)

void elem_print(struct simap_elem *n, void *u) {
  printf(" (%s, %d)", n->key, n->value);
}

int main() {
  struct simap *si = simap(10, hash_s, strcmp);
  simap_put(si, "abc", 12);
  simap_put(si, "def", 35);
  simap_put(si, "ace", 28);
  printf("size = %d cap = %d\n", si->size, si->cap);
  simap_trav(si, elem_print, NULL);
  printf("\n");
  simap_free(si);
}