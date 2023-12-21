#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*compare_fnt)(const void *p1, const void *p2);
typedef void (*destructor_fnt)(void *p);
static inline int cmpl(const void *p1, const void *p2) {
  return *(const int *)p1 - *(const int *)p2;
}
static inline int rcmpl(const void *p1, const void *p2) {
  return *(const int *)p2 - *(const int *)p1;
}
static inline int cmpd(const void *p1, const void *p2) {
  double v1 = *(const double *)p1, v2 = *(const double *)p2;
  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  }
  return 0;
}
static inline int rcmpd(const void *p1, const void *p2) {
  double v2 = *(const double *)p1, v1 = *(const double *)p2;
  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  }
  return 0;
}
static inline int cmps(const void *p1, const void *p2) {
  char *const *s1 = p1, *const *s2 = p2;
  return strcmp(*s1, *s2);
}
static inline int rcmps(const void *p1, const void *p2) {
  char *const *s2 = p1, *const *s1 = p2;
  return strcmp(*s1, *s2);
}
static inline void frees(void *p) { free(*(char **)p); }
enum tcolors { RED = 0, BLACK = 1 };
struct simap_node {
  char *key;
  int value;
  enum tcolors color;
  struct simap_node *left;
  struct simap_node *right;
  struct simap_node *top;
};
struct simap {
  struct simap_node *root;
  compare_fnt cmp;
  destructor_fnt fk, fv;
  long size;
};
struct simap_node *sileft_most(struct simap_node *n);
struct simap_node *siright_most(struct simap_node *n);
struct simap_node *sileft_deepest(struct simap_node *n);
struct simap_node *sinext_lrn(struct simap_node *n);
struct simap_node *sinext_lnr(struct simap_node *n);
struct simap_node *siprev_lnr(struct simap_node *n);
struct simap_node *sifirst_lrn(struct simap *t);
struct simap_node *sifirst_lnr(struct simap *t);
struct simap_node *silast_lnr(struct simap *t);
struct simap *sicreate(compare_fnt cmp);
struct simap *simap(compare_fnt cmp);
int *siput(struct simap *t, char *key, int value);
int *siget(struct simap *t, char *key);
struct simap *siremove(struct simap *t, char *key);
void sifree(void *po);
struct simap_node *simap_node(char *key, int value) {
  struct simap_node *nn = malloc(sizeof(struct simap_node));
  nn->key = key;
  nn->value = value;
  (nn)->color = RED;
  nn->left = nn->right = nn->top = ((void *)0);
  return nn;
}
struct simap_node *sileft_most(struct simap_node *n) {
  while (n->left) {
    n = n->left;
  }
  return n;
}
struct simap_node *siright_most(struct simap_node *n) {
  while (n->right) {
    n = n->right;
  }
  return n;
}
struct simap_node *sileft_deepest(struct simap_node *n) {
  for (;;) {
    if (n->left) {
      n = n->left;
    } else if (n->right) {
      n = n->right;
    } else {
      break;
    }
  }
  return n;
}
struct simap_node *sinext_lrn(struct simap_node *n) {
  struct simap_node *top = n->top;
  if (top && n == top->left && top->right) {
    return sileft_deepest(top->right);
  }
  return top;
}
struct simap_node *sinext_lnr(struct simap_node *n) {
  if (n->right) {
    return sileft_most(n->right);
  }
  struct simap_node *top = n->top;
  while (top != ((void *)0) && n == top->right) {
    n = top;
    top = n->top;
  }
  return top;
}
struct simap_node *siprev_lnr(struct simap_node *n) {
  if (n->left) {
    return siright_most(n->left);
  }
  struct simap_node *top = n->top;
  while (top != ((void *)0) && n == top->left) {
    n = top;
    top = n->top;
  }
  return top;
}
struct simap_node *sifirst_lrn(struct simap *t) {
  return sileft_deepest(t->root);
}
struct simap_node *sifirst_lnr(struct simap *t) {
  return sileft_most(t->root);
}
struct simap_node *silast_lnr(struct simap *t) {
  return siright_most(t->root);
}
struct simap *sicreate(compare_fnt cmp) {
  if (!cmp) {
    ;
    return ((void *)0);
  }
  struct simap *t = malloc(sizeof(struct simap));
  if (!t) {
    ;
    return ((void *)0);
  }
  t->root = ((void *)0);
  t->cmp = cmp;
  t->fv = t->fk = ((void *)0);
  t->size = 0;
  return t;
}
struct simap *simap(compare_fnt cmp) {
  return sicreate(cmp);
}
static struct simap *sidelete(struct simap *t, struct simap_node *dn) {
  struct simap_node *node = dn;
  struct simap_node *child = node->right, *tmp = node->left, *parent,
                    *rebalance;
  struct simap_node *p;
  enum tcolors c;
  if (!tmp) {
    p = node->top;
    c = node->color;
    parent = p;
    do {
      if (parent) {
        if (parent->left == node) {
          parent->left = child;
        } else {
          parent->right = child;
        }
      } else {
        t->root = child;
      }
    } while (0);
    if (child) {
      (child)->top = (p);
      (child)->color = (c);
      rebalance = ((void *)0);
    } else {
      rebalance = c == BLACK ? parent : ((void *)0);
    }
    tmp = parent;
  } else if (!child) {
    p = node->top;
    c = node->color;
    (tmp)->top = (p);
    (tmp)->color = (c);
    parent = p;
    do {
      if (parent) {
        if (parent->left == node) {
          parent->left = tmp;
        } else {
          parent->right = tmp;
        }
      } else {
        t->root = tmp;
      }
    } while (0);
    rebalance = ((void *)0);
    tmp = parent;
  } else {
    struct simap_node *successor = child, *child2;
    tmp = child->left;
    if (!tmp) {
      parent = successor;
      child2 = successor->right;
    } else {
      do {
        parent = successor;
        successor = tmp;
        tmp = tmp->left;
      } while (tmp);
      child2 = successor->right;
      parent->left = child2;
      successor->right = child;
      child->top = successor;
    }
    tmp = node->left;
    successor->left = tmp;
    tmp->top = successor;
    p = node->top;
    c = node->color;
    tmp = p;
    do {
      if (tmp) {
        if (tmp->left == node) {
          tmp->left = successor;
        } else {
          tmp->right = successor;
        }
      } else {
        t->root = successor;
      }
    } while (0);
    if (child2) {
      (child2)->top = (parent);
      (child2)->color = (BLACK);
      rebalance = ((void *)0);
    } else {
      enum tcolors c2 = successor->color;
      rebalance = c2 == BLACK ? parent : ((void *)0);
    }
    (successor)->top = (p);
    (successor)->color = (c);
    tmp = successor;
  }
  if (rebalance) {
    struct simap_node *n, *s, *cn, *dn, *u_;
    do {
      n = ((void *)0);
      while (1) {
        s = rebalance->right;
        if (n != s) {
          if (((s) && (s)->color == RED)) {
            do {
              u_ = (rebalance)->right;
              (rebalance)->right = u_->left;
              if (u_->left != ((void *)0)) {
                u_->left->top = (rebalance);
              }
              u_->top = (rebalance)->top;
              do {
                if ((rebalance)->top) {
                  if ((rebalance)->top->left == rebalance) {
                    (rebalance)->top->left = u_;
                  } else {
                    (rebalance)->top->right = u_;
                  }
                } else {
                  t->root = u_;
                }
              } while (0);
              u_->left = (rebalance);
              (rebalance)->top = u_;
            } while (0);
            (rebalance)->color = RED;
            (s)->color = BLACK;
            s = rebalance->right;
          }
          dn = s->right;
          if ((!(dn) || (dn)->color == BLACK)) {
            cn = s->left;
            if ((!(cn) || (cn)->color == BLACK)) {
              (s)->color = RED;
              if (((rebalance) && (rebalance)->color == RED)) {
                (rebalance)->color = BLACK;
              } else {
                n = rebalance;
                rebalance = n->top;
                if (rebalance) {
                  continue;
                }
              }
              break;
            }
            do {
              u_ = (s)->left;
              (s)->left = u_->right;
              if (u_->right != ((void *)0)) {
                u_->right->top = (s);
              }
              u_->top = (s)->top;
              do {
                if ((s)->top) {
                  if ((s)->top->left == s) {
                    (s)->top->left = u_;
                  } else {
                    (s)->top->right = u_;
                  }
                } else {
                  t->root = u_;
                }
              } while (0);
              u_->right = (s);
              (s)->top = u_;
            } while (0);
            s = rebalance->right;
          }
          dn = s->right;
          do {
            u_ = (rebalance)->right;
            (rebalance)->right = u_->left;
            if (u_->left != ((void *)0)) {
              u_->left->top = (rebalance);
            }
            u_->top = (rebalance)->top;
            do {
              if ((rebalance)->top) {
                if ((rebalance)->top->left == rebalance) {
                  (rebalance)->top->left = u_;
                } else {
                  (rebalance)->top->right = u_;
                }
              } else {
                t->root = u_;
              }
            } while (0);
            u_->left = (rebalance);
            (rebalance)->top = u_;
          } while (0);
          (s)->color = (rebalance->color);
          (rebalance)->color = BLACK;
          (dn)->color = BLACK;
          break;
        } else {
          s = rebalance->left;
          if (((s) && (s)->color == RED)) {
            do {
              u_ = (rebalance)->left;
              (rebalance)->left = u_->right;
              if (u_->right != ((void *)0)) {
                u_->right->top = (rebalance);
              }
              u_->top = (rebalance)->top;
              do {
                if ((rebalance)->top) {
                  if ((rebalance)->top->left == rebalance) {
                    (rebalance)->top->left = u_;
                  } else {
                    (rebalance)->top->right = u_;
                  }
                } else {
                  t->root = u_;
                }
              } while (0);
              u_->right = (rebalance);
              (rebalance)->top = u_;
            } while (0);
            (rebalance)->color = RED;
            (s)->color = BLACK;
            s = rebalance->left;
          }
          dn = s->left;
          if ((!(dn) || (dn)->color == BLACK)) {
            cn = s->right;
            if ((!(cn) || (cn)->color == BLACK)) {
              (s)->color = RED;
              if (((rebalance) && (rebalance)->color == RED)) {
                (rebalance)->color = BLACK;
              } else {
                n = rebalance;
                rebalance = n->top;
                if (rebalance) {
                  continue;
                }
              }
              break;
            }
            do {
              u_ = (s)->right;
              (s)->right = u_->left;
              if (u_->left != ((void *)0)) {
                u_->left->top = (s);
              }
              u_->top = (s)->top;
              do {
                if ((s)->top) {
                  if ((s)->top->left == s) {
                    (s)->top->left = u_;
                  } else {
                    (s)->top->right = u_;
                  }
                } else {
                  t->root = u_;
                }
              } while (0);
              u_->left = (s);
              (s)->top = u_;
            } while (0);
            s = rebalance->left;
          }
          dn = s->left;
          do {
            u_ = (rebalance)->left;
            (rebalance)->left = u_->right;
            if (u_->right != ((void *)0)) {
              u_->right->top = (rebalance);
            }
            u_->top = (rebalance)->top;
            do {
              if ((rebalance)->top) {
                if ((rebalance)->top->left == rebalance) {
                  (rebalance)->top->left = u_;
                } else {
                  (rebalance)->top->right = u_;
                }
              } else {
                t->root = u_;
              }
            } while (0);
            u_->right = (rebalance);
            (rebalance)->top = u_;
          } while (0);
          (s)->color = (rebalance->color);
          (rebalance)->color = BLACK;
          (dn)->color = BLACK;
          break;
        }
      }
    } while (0);
  }
  free(dn);
  return t;
}
int *siput(struct simap *t, char *key, int value) {
  struct simap_node *nn = simap_node(key, value);
  struct simap_node *top = ((void *)0);
  struct simap_node *x = t->root;
  struct simap_node **loc = &t->root;
  int rl = 0;
  while (x) {
    rl = t->cmp(&key, &x->key);
    if (rl == 0) {
      free(nn);
      return &x->value;
    }
    top = x;
    if (rl < 0) {
      x = top->left;
      loc = &top->left;
    } else {
      x = top->right;
      loc = &top->right;
    }
  }
  *loc = nn;
  nn->top = top;
  if (top == ((void *)0)) {
    nn->color = BLACK;
  } else if (((top) && (top)->color == RED)) {
    struct simap_node *y_;
    do {
      while (1) {
        if (top == top->top->left) {
          if (((top->top->right) && (top->top->right)->color == RED)) {
            (top)->color = BLACK;
            (top->top->right)->color = BLACK;
            (top->top)->color = RED;
            nn = top->top;
            top = nn->top;
            if (top == ((void *)0)) {
              (nn)->color = BLACK;
              break;
            }
            if ((!(top) || (top)->color == BLACK)) {
              break;
            }
          } else {
            if (nn == nn->top->right) {
              do {
                y_ = (top)->right;
                (top)->right = y_->left;
                if (y_->left != ((void *)0)) {
                  y_->left->top = (top);
                }
                y_->top = (top)->top;
                do {
                  if ((top)->top) {
                    if ((top)->top->left == top) {
                      (top)->top->left = y_;
                    } else {
                      (top)->top->right = y_;
                    }
                  } else {
                    t->root = y_;
                  }
                } while (0);
                y_->left = (top);
                (top)->top = y_;
              } while (0);
              nn = top;
              top = nn->top;
            }
            (top)->color = BLACK;
            (top->top)->color = RED;
            top = top->top;
            do {
              y_ = (top)->left;
              (top)->left = y_->right;
              if (y_->right != ((void *)0)) {
                y_->right->top = (top);
              }
              y_->top = (top)->top;
              do {
                if ((top)->top) {
                  if ((top)->top->left == top) {
                    (top)->top->left = y_;
                  } else {
                    (top)->top->right = y_;
                  }
                } else {
                  t->root = y_;
                }
              } while (0);
              y_->right = (top);
              (top)->top = y_;
            } while (0);
            break;
          }
        } else {
          if (((top->top->left) && (top->top->left)->color == RED)) {
            (top)->color = BLACK;
            (top->top->left)->color = BLACK;
            (top->top)->color = RED;
            nn = top->top;
            top = nn->top;
            if (top == ((void *)0)) {
              (nn)->color = BLACK;
              break;
            }
            if ((!(top) || (top)->color == BLACK)) {
              break;
            }
          } else {
            if (nn == nn->top->left) {
              do {
                y_ = (top)->left;
                (top)->left = y_->right;
                if (y_->right != ((void *)0)) {
                  y_->right->top = (top);
                }
                y_->top = (top)->top;
                do {
                  if ((top)->top) {
                    if ((top)->top->left == top) {
                      (top)->top->left = y_;
                    } else {
                      (top)->top->right = y_;
                    }
                  } else {
                    t->root = y_;
                  }
                } while (0);
                y_->right = (top);
                (top)->top = y_;
              } while (0);
              nn = top;
              top = nn->top;
            }
            (top)->color = BLACK;
            (top->top)->color = RED;
            top = top->top;
            do {
              y_ = (top)->right;
              (top)->right = y_->left;
              if (y_->left != ((void *)0)) {
                y_->left->top = (top);
              }
              y_->top = (top)->top;
              do {
                if ((top)->top) {
                  if ((top)->top->left == top) {
                    (top)->top->left = y_;
                  } else {
                    (top)->top->right = y_;
                  }
                } else {
                  t->root = y_;
                }
              } while (0);
              y_->left = (top);
              (top)->top = y_;
            } while (0);
            break;
          }
        }
      }
    } while (0);
  }
  ++t->size;
  return ((void *)0);
}
int *siget(struct simap *t, char *key) {
  struct simap_node *x;
  do {
    int rl;
    x = t->root;
    while (x) {
      rl = t->cmp(&key, &x->key);
      if (rl == 0) {
        break;
      }
      x = rl < 0 ? x->left : x->right;
    }
  } while (0);
  if (!x) {
    return ((void *)0);
  }
  return &x->value;
}
struct simap *siremove(struct simap *t, char *key) {
  struct simap_node *n;
  do {
    int rl;
    n = t->root;
    while (n) {
      rl = t->cmp(&key, &n->key);
      if (rl == 0) {
        break;
      }
      n = rl < 0 ? n->left : n->right;
    }
  } while (0);
  if (!n) {
    return ((void *)0);
  }
  if (t->fk) {
    t->fk(&n->key);
  }
  if (t->fv) {
    t->fv(&n->value);
  }
  sidelete(t, n);
  --(t->size);
  return t;
}
void sifree(void *po) {
  struct simap *t = po;
  struct simap_node *n = sifirst_lrn(t);
  struct simap_node *tmp = ((void *)0);
  while (n) {
    if (t->fk) {
      t->fk(&n->key);
    }
    if (t->fv) {
      t->fv(&n->value);
    }
    tmp = n;
    n = sinext_lrn(n);
    free(tmp);
  }
  free(t);
};
int main() {
  char key[100];
  struct simap *si = simap(cmps);
  si->fk = frees;
  while (scanf("%s", key) == 1) {
    int *value = siget(si, key);
    if (value) {
      ++(*value);
    } else {
      siput(si, strdup(key), 1);
    }
  }
  struct simap_node *nd = sifirst_lnr(si);
  while (nd) {
    printf("%s: %d\n", nd->key, nd->value);
    nd = sinext_lnr(nd);
  }
  sifree(si);
}
