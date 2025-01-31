#include "tmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

TMAP_DECL_IMPL(simap, char *, int)

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
  struct simap *si = simap(strcmp);
  si->fk = free;
  for (int i = 0; i < 100000; ++i) {
    char *key = strdup(gens());
    struct simap_node *n = simap_put(si, key, rand());
    if (n) {
      printf("Trùng khóa: %s\n", n->key);
      free(key);
    }
  }
  simap_free(si);
}