/* (C) Nguyễn Bá Ngọc 2025 */

#ifndef TNAV_H_
#define TNAV_H_

enum nav_dir {
  LEFT,
  RIGHT,
  NODE
};

#define TNAV_DECL(tname) \
struct tname##_node *tname##_left_most(struct tname##_node *n); \
struct tname##_node *tname##_right_most(struct tname##_node *n); \
struct tname##_node *tname##_left_deepest(struct tname##_node *n); \
struct tname##_node *tname##_first_lrn(struct tname *tm); \
struct tname##_node *tname##_next_lrn(struct tname##_node *n); \
struct tname##_node *tname##_first_lnr(struct tname *tm); \
struct tname##_node *tname##_next_lnr(struct tname##_node *n); \
struct tname##_node *tname##_next_rnl(struct tname##_node *n); \
struct tname##_node *tname##_first_rnl(struct tname *tm); \
void tname##_trav(struct tname *tm, void (*f)(struct tname##_node *n, void *u), void *u); \
void tname##_walk(struct tname##_node *n, void (*f)(struct tname##_node *n, void *u), \
                     void *u, enum nav_dir first, enum nav_dir second, enum nav_dir third);

#define DIR_SWITCH(traverse, key) \
  switch (key) { \
    case LEFT: \
      if (n->left) { \
        traverse(n->left, f, u, first, second, third); \
      } \
      break; \
    case RIGHT: \
      if (n->right) { \
        traverse(n->right, f, u, first, second, third); \
      } \
      break; \
    case NODE: \
      f(n, u); \
      break; \
  }

#define TNAV_IMPL(tname) \
void tname##_walk(struct tname##_node *n, void (*f)(struct tname##_node *n, void *u), \
                     void *u, enum nav_dir first, enum nav_dir second, enum nav_dir third) { \
  DIR_SWITCH(tname##_walk, first) \
  DIR_SWITCH(tname##_walk, second) \
  DIR_SWITCH(tname##_walk, third) \
} \
void tname##_trav(struct tname *tm, void (*f)(struct tname##_node *n, void *u), void *u) { \
  if (!tm) { \
    return ; \
  } \
  tname##_walk(tm->root, f, u, LEFT, NODE, RIGHT); \
} \
struct tname##_node *tname##_left_most(struct tname##_node *n) { \
  while (n->left) { \
    n = n->left; \
  } \
  return n; \
} \
struct tname##_node *tname##_right_most(struct tname##_node *n) { \
  while (n->right) { \
    n = n->right; \
  } \
  return n; \
} \
struct tname##_node *tname##_left_deepest(struct tname##_node *n) { \
  for (;;) { \
    if (n->left) { \
      n = n->left; \
    } else if (n->right) { \
      n = n->right; \
    } else { \
      break; \
    } \
  } \
  return n; \
} \
struct tname##_node *tname##_first_lnr(struct tname *tm) { \
  return tm->root? tname##_left_most(tm->root): NULL; \
} \
struct tname##_node *tname##_next_lnr(struct tname##_node *n) { \
  if (n->right) { \
    return tname##_left_most(n->right); \
  } \
  struct tname##_node *top = n->top; \
  while (top != NULL && n == top->right) { \
    n = top; \
    top = n->top; \
  } \
  return top; \
} \
struct tname##_node *tname##_first_rnl(struct tname *tm) { \
  return tm->root? tname##_right_most(tm->root): NULL; \
} \
struct tname##_node *tname##_next_rnl(struct tname##_node *n) { \
  if (n->left) { \
    return tname##_right_most(n->left); \
  } \
  struct tname##_node *top = n->top; \
  while (top != NULL && n == top->left) { \
    n = top; \
    top = n->top; \
  } \
  return top; \
} \
struct tname##_node *tname##_first_lrn(struct tname *tm) { \
  return tm->root? tname##_left_deepest(tm->root): NULL; \
} \
struct tname##_node *tname##_next_lrn(struct tname##_node *n) { \
  struct tname##_node *top = n->top; \
  if (top && n == top->left && top->right) { \
    return tname##_left_deepest(top->right); \
  } \
  return top; \
}

#define TNAV_DECL_IMPL(tname) \
TNAV_DECL(tname) \
TNAV_IMPL(tname)

#endif  // TNAV_H_