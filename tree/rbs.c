/* (C) Nguyen Ba Ngoc 2021 */

#include "tree/rbs.h"

#include <stdlib.h>

struct rbs *rbs_create(gtype_cmp_t cmp, gtype_free_t fk) {
  struct grbt *tmp = grb_create_tree(NULL, cmp, fk);
  struct rbs *s = realloc(tmp, sizeof(struct rbs));
  s->size = 0;
  return s;
}

int rbs_insert(struct rbs *s, gtype elem) {
  struct bs_ires ires = grb_insert_unique(grb_tree(s), elem);
  if (ires.inserted) {
    ++(s->size);
  }
  return ires.inserted;
}

struct grbn *rbs_search(struct rbs *s, gtype elem) {
  return grb_search(grb_tree(s), elem);
}

int rbs_remove(struct rbs *s, gtype elem) {
  struct grbn *n = rbs_search(s, elem);
  if (!n) {
    return 0;
  }
  grb_delete(grb_tree(s), n);
  --s->size;
  return 1;
}

void gtype_free_rbs(gtype value) {
  rbs_free(value.rbs);
}
