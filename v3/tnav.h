/* (C) Nguyễn Bá Ngọc 2025 */

#ifndef TNAV_H_
#define TNAV_H_

#define TNAV_DECL(tname) \
struct tname##_node *tname##_left_most(struct tname##_node *n); \
struct tname##_node *tname##_right_most(struct tname##_node *n); \
struct tname##_node *tname##_left_deepest(struct tname##_node *n); \
struct tname##_node *tname##_next_lrn(struct tname##_node *n); \
struct tname##_node *tname##_next_lnr(struct tname##_node *n); \
struct tname##_node *tname##_prev_lnr(struct tname##_node *n); \
struct tname##_node *tname##_first_lrn(struct tname *tm); \
struct tname##_node *tname##_first_lnr(struct tname *tm); \
struct tname##_node *tname##_last_lnr(struct tname *tm);


#define TNAV_IMPL(tname) \
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
struct tname##_node *tname##_next_lrn(struct tname##_node *n) { \
  struct tname##_node *top = n->top; \
  if (top && n == top->left && top->right) { \
    return tname##_left_deepest(top->right); \
  } \
  return top; \
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
struct tname##_node *tname##_prev_lnr(struct tname##_node *n) { \
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
struct tname##_node *tname##_first_lnr(struct tname *tm) { \
  return tm->root? tname##_left_most(tm->root): NULL; \
} \
struct tname##_node *tname##_last_lnr(struct tname *tm) { \
  return tm->root? tname##_right_most(tm->root): NULL; \
} \

#endif  // TNAV_H_