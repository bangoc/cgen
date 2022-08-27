/*
  (C) Nguyen Ba Ngoc 2021
*/

#include "spec/s2i.h"

#include <string.h>

s2i_t s2i_create() {
  bn_tree_t t = bn_create_tree(NULL);
  s2i_t s2i = realloc(t, sizeof(struct s2i_s));
  s2i->invalid_id = -1;
  return s2i;
}

int s2i_compare_data(const char *q, bn_node_t n) {
  const char *s1 = (char*)q;
  const char *s2 = s2i_node_key(n);
  return strcmp(s1, s2);
}

s2i_node_t s2i_create_node(const char *key, long value) {
  s2i_node_t n = calloc(1, sizeof(struct s2i_node));
  n->key = strdup(key);
  n->value = value;
  return n;
}

s2i_node_t s2i_insert(s2i_t si, const char *key, long value) {
  bn_node_t same = NULL, parent = NULL;
  bn_node_t *loc;
  bn_tree_t t = (bn_tree_t)si;
  bns_insert_setup(loc, t->root, key, s2i_compare_data, same, parent);
  if (same) {
    return to_s2i(same);
  }
  s2i_node_t n = s2i_create_node(key, value);
  rb_insert(t, bn_node(n), loc, parent);
  return n;
}

s2i_node_t s2i_set(s2i_t si, const char *key, long value) {
  bn_node_t same = NULL, parent = NULL;
  bn_node_t *loc;
  bn_tree_t t = (bn_tree_t)si;
  bns_insert_setup(loc, t->root, key, s2i_compare_data, same, parent);
  if (same) {
    s2i_node_value(same) = value;
    return to_s2i(same);
  }
  s2i_node_t n = s2i_create_node(key, value);
  rb_insert(t, bn_node(n), loc, parent);
  return n;
}

s2i_node_t s2i_search(s2i_t si, const char *key) {
  bn_tree_t t = (bn_tree_t)si;
  bns_search_inline(result, t, key, s2i_compare_data, return to_s2i(result));
}

long *s2i_vref(s2i_t si, const char *key) {
  s2i_node_t n = s2i_search(si, key);
  if (n) {
    return &(n->value);
  }
  return NULL;
}

long s2i_value(s2i_t si, const char *key) {
  long *value = s2i_vref(si, key);
  if (value) {
    return *value;
  }
  return si->invalid_id;
}

int s2i_delete(s2i_t si, const char *key) {
  s2i_node_t n = s2i_search(si, key);
  if (n) {
    rb_delete((bn_tree_t)si, bn_node(n));
    s2i_free_node(n);
    return 1;
  }
  return 0;
}

void s2i_free_node(s2i_node_t n) {
  free(n->key);
  free(n);
}

void s2i_free(s2i_t si) {
  bn_tree_t t = (bn_tree_t)si;
  bn_traverse_lnr(cur, t) {
    free(to_s2i(cur)->key);
  }
  bn_free_tree(t);
}

void s2i_postorder_print(s2i_t si) {
  bn_tree_t t = (bn_tree_t)si;
  bn_traverse_lrn(cur, t) {
    printf("%s: %ld\n", s2i_node_key(cur), s2i_node_value(cur));
  }
}

void s2i_print_node(s2i_node_t n) {
  printf("(%s, %ld) - %s\n", n->key, n->value, rb_color_str(n));
}
