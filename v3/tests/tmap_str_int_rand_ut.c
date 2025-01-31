#include "tmap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

TMAP_DECL_IMPL(tmap, char *, int)

const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const int n = sizeof(letters) - 1;

char *gens() {
  static char buff[11];
  int len = rand() % 5 + 1;
  for (int i = 0; i < len; ++i) {
    buff[i] = letters[rand() % n];
  }
  buff[len] = 0;
  return buff;
}

static long rb_back_height = -1;
static int rb_is_invalid = 0;

static int rb_is_valid_internal(struct tmap_node *n, long blacks) {
  if (rb_is_invalid) {
    return 0;
  }
  if (n == NULL) {
    if (rb_back_height < 0) {
      rb_back_height = blacks;
      return 1;  /* Ok */
    } else if (rb_back_height != blacks) {
      printf("Tính chất 5.\n");
      rb_is_invalid = 1;
      return 0;
    }
    return 1; /* Ok */
  }
  if (IS_RED(n)) {
    if (IS_RED(n->left) || IS_RED(n->right)) {
      printf("Tính chất 4.\n");
      rb_is_invalid = 1;
      return 0;
    }
    return rb_is_valid_internal(n->left, blacks) &&
        rb_is_valid_internal(n->right, blacks);
  } else if (IS_BLACK(n)) {
    return rb_is_valid_internal(n->left, blacks + 1) &&
        rb_is_valid_internal(n->right, blacks + 1);
  }
  printf("Tính chất 1.\n");
  rb_is_invalid = 1;
  return 0;
}

static int rb_is_valid(struct tmap *t) {
  if (t->root == NULL) {
    return 1;
  }
  if (IS_RED(t->root)) {
    printf("Tính chất 2.\n");
    return 0;
  }
  rb_back_height = -1;
  rb_is_invalid = 0;
  return rb_is_valid_internal(t->root, 0);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: ./prog 10000\n");
    return 1;
  }
  struct tmap *tm = tmap(strcmp);
  tm->fk = free;
  int n;
  sscanf(argv[1], "%d", &n);
  srand(time(NULL));
  for (int i = 0; i < n; ++i) {
    int c = rand() % 5;
    switch (c) {
    case 1: case 2:
      tmap_rem(tm, gens());
      if (!rb_is_valid(tm)) {
        printf("Rb is not valid!\n");
        return 1;
      }
      break;
    default: {
        char *s = strdup(gens());
        if (tmap_put(tm, s, rand())) {
          free(s);
        }
        if (!rb_is_valid(tm)) {
          printf("Rb is not valid!\n");
          return 1;
        }
      }
    }
  }
  tmap_free(tm);
  printf("Test Ok\n");
}