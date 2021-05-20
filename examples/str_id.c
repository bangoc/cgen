#include "s2i.h"
#include "svector.h"

#include <string.h>
#include <stdlib.h>

typedef struct str_cache {
  bn_tree_t si;
  vector_t is;
} *str_cache_t;

void cache_print(str_cache_t cache) {
  s2i_postorder_print(cache->si);
  svec_print(cache->is);
}

str_cache_t create_cache() {
  str_cache_t sc = malloc(sizeof(struct str_cache));
  sc->si = bn_create_tree(NULL);
  sc->is = gtv_create();
}

long get_save_str_id(str_cache_t cache, char *s) {
  long id = s2i_value(cache->si, s);
  if (id != k_s2i_invalid) {
    return id;
  }
  svec_push_back(&cache->is, s);
  id = gtv_size(cache->is) - 1;
  s2i_insert(cache->si, s, id);
  return id;
}

char *get_by_id(str_cache_t cache, long id) {
  if (id >= 0 && id < gtv_size(cache->is)) {
    return cache->is[id].s;
  }
  return NULL;
}

void free_cache(str_cache_t *cache) {
  s2i_free(&(*cache)->si);
  gtv_free(&(*cache)->is);
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