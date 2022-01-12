#include "base/arr.h"
#include "spec/s2i.h"

#include <string.h>
#include <stdlib.h>

typedef struct str_cache {
  s2i_t si;
  arr_t(char*) is;
} *str_cache_t;

void as_print(arr_t(char*) is) {
  for (int i = 0; i < arr_size(is); ++i) {
    printf("%-5d: %s\n", i, ARR(is)[i]);
  }
}

void cache_print(str_cache_t cache) {
  s2i_postorder_print(cache->si);
  as_print(cache->is);
}

str_cache_t create_cache() {
  str_cache_t sc = malloc(sizeof(struct str_cache));
  sc->si = s2i_create();
  sc->is = arr_create(0, char*);
  return sc;
}

long get_save_str_id(str_cache_t cache, char *s) {
  long *id = s2i_vref(cache->si, s);
  if (id) {
    return *id;
  }
  arr_append(cache->is, strdup(s));
  long id2 = arr_size(cache->is) - 1;
  s2i_insert(cache->si, s, id2);
  return id2;
}

char *get_by_id(str_cache_t cache, long id) {
  if (id >= 0 && id < arr_size(cache->is)) {
    return ARR(cache->is)[id];
  }
  return NULL;
}

void free_cache(str_cache_t *cache) {
  s2i_free((*cache)->si);
  for (int i = 0; i < arr_size((*cache)->is); ++i) {
    free(ARR((*cache)->is)[i]);
  }
  arr_free((*cache)->is);
  free(*cache);
  *cache = NULL;
}

int main() {
  char s[100];
  str_cache_t cache = create_cache();
  for (;;) {
    printf("Input s: ");
    scanf("%s", s);
    if (strcmp(s, "stop") == 0) {
      break;
    }
    long id = get_save_str_id(cache, s);
    printf("Id = %ld\n", id);
    cache_print(cache);
  }
  for (;;) {
    printf("Input id: ");
    long id;
    scanf("%ld", &id);
    if (id < 0) {
      break;
    }
    char *s = get_by_id(cache, id);
    if (s) {
      printf("String with id %ld is %s\n", id, s);
    } else {
      printf("Not found\n");
    }
  }
  free_cache(&cache);
  return 0;
}
