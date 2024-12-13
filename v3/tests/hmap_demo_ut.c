#include "hmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

HMAP_DECL_IMPL(sihmap, char *, int)

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
  struct sihmap *hm = sihmap(0, hash_s, eq_s);
  for (int i = 0; i < 100000; ++i) {
    char *key = strdup(gens());
    struct sihmap_node *n = sihmap_put(hm, key, rand());
    if (n) {
      printf("Trùng khóa: %s\n", n->key);
      free(key);
    }
  }
  for (struct sihmap_node *n = sihmap_first(hm); n; n = sihmap_next(hm, n)) {
    printf("%s: %d\n", n->key, *sihmap_get(hm, n->key));
  }
  for (struct sihmap_node *n = sihmap_first(hm); n; n = sihmap_next(hm, n)) {
    free(n->key);
  }
  sihmap_del(hm);
}