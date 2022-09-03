/* (C) Nguyen Ba Ngoc 2022 */

#include "mix/s2w.h"

s2w_t s2w_create() {
  s2w_t col = malloc(sizeof(struct string_index_2way));
  col->is = gvec_create(0, NULL);
  col->si = s2i_create();
  return col;
}

rbm_ires s2w_insert(s2w_t col, const char *s) {
  long id = gvec_size(col->is);
  rbm_ires r = s2i_insert(col->si, s, id);
  if (r.inserted) {
    char *key = rbm_node(
      container_of(r.value, struct red_black_map_node, value))->key.s;
        gvec_append(col->is, gtype_s(key));
  }
  return r;
}

long *s2w_put(s2w_t col, const char *s) {
  long id = gvec_size(col->is);
  rbm_ires r = s2i_insert(col->si, s, id);
  if (!r.inserted) {
    return r.value;
  }
  char *key = rbm_node(
    container_of(r.value, struct red_black_map_node, value))->key.s;
  gvec_append(col->is, gtype_s(key));
  return NULL;
}

int s2w_remove(s2w_t col, const char *s) {
  long id = s2w_id(col, s);
  if (id < 0) {
    return 0;
  }
  gvec_elem(col->is, id).s = NULL;
  return s2i_remove(col->si, s);
}

long s2w_id(s2w_t col, const char *s) {
  long *tmp = s2i_value(col->si, s);
  if (!tmp) {
    return -1;
  }
  return *tmp;
}

char *s2w_str(s2w_t col, const long id) {
  long sz = gvec_size(col->is);
  if (id < 0 || id >= sz) {
    return NULL;
  }
  return gvec_elem(col->is, id).s;
}

void s2w_free(s2w_t col) {
  s2i_free(col->si);
  gvec_free(col->is);
  free(col);
}