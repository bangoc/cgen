/* (C) Nguyen Ba Ngoc 2022 */

#include "mix/s2w.h"

struct s2w *s2w_create() {
  struct s2w *col = malloc(sizeof(struct s2w));
  col->is = gvec_create(0, NULL);
  col->si = s2i_create();
  return col;
}

struct rbm_ires s2w_insert(struct s2w *col, const char *s) {
  long id = gvec_size(col->is);
  struct rbm_ires r = s2i_insert(col->si, s, id);
  if (r.inserted) {
    char *key = rbm_node(
      container_of(r.value, struct rbmn, value))->key.s;
        gvec_append(col->is, gtype_s(key));
  }
  return r;
}

long *s2w_put(struct s2w *col, const char *s) {
  long id = gvec_size(col->is);
  struct rbm_ires r = s2i_insert(col->si, s, id);
  if (!r.inserted) {
    return r.value;
  }
  char *key = rbm_node(
    container_of(r.value, struct rbmn, value))->key.s;
  gvec_append(col->is, gtype_s(key));
  return NULL;
}

int s2w_remove(struct s2w *col, const char *s) {
  long id = s2w_id(col, s);
  if (id < 0) {
    return 0;
  }
  gvec_elem(col->is, id).s = NULL;
  return s2i_remove(col->si, s);
}

long s2w_id(struct s2w *col, const char *s) {
  long *tmp = s2i_value(col->si, s);
  if (!tmp) {
    return -1;
  }
  return *tmp;
}

char *s2w_str(struct s2w *col, const long id) {
  long sz = gvec_size(col->is);
  if (id < 0 || id >= sz) {
    return NULL;
  }
  return gvec_elem(col->is, id).s;
}

void s2w_free(struct s2w *col) {
  s2i_free(col->si);
  gvec_free(col->is);
  free(col);
}