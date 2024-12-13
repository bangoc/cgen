#ifndef HMAP_H_
#define HMAP_H_

#include <stdlib.h>
#include <string.h>

enum hmap_node_state {
  UNUSED = 0,
  USING,
  DELETED,
  STATE_COUNT
};

const int prime_mod [] =
{
  1,          /* 1 << 0 */
  2,
  3,
  7,
  13,
  31,
  61,
  127,
  251,
  509,
  1021,
  2039,
  4093,
  8191,
  16381,
  32749,
  65521,      /* 1 << 16 */
  131071,
  262139,
  524287,
  1048573,
  2097143,
  4194301,
  8388593,
  16777213,
  33554393,
  67108859,
  134217689,
  268435399,
  536870909,
  1073741789,
  2147483647  /* 1 << 31 */
};

#define HASH_MIN_SHIFT 3

#define HASH2IDX(hm, hash)(((hash) * 11) % (hm)->mod)

#define GET_BIT(bitmap, index) (((bitmap)[(index) / 8] >> ((index) % 8)) & 1)
#define SET_BIT(bitmap, index) ((bitmap)[(index) / 8] |= 1U << ((index) % 8))

#define HMAP_DECL(pre, key_t, value_t) \
struct pre##hmap_node; \
struct pre##hmap; \
struct pre##hmap *pre##hmap(int cap, unsigned (*ha)(), int (*eq)()); \
struct pre##hmap_node *pre##hmap_put(struct pre##hmap *hm, key_t k, value_t v); \
value_t *pre##hmap_get(struct pre##hmap *hm, key_t k); \
struct pre##hmap_node *pre##hmap_rem(struct pre##hmap *hm, key_t k); \
void pre##hmap_del(struct pre##hmap *hm);

#define HMAP_IMPL(pre, key_t, value_t) \
struct pre##hmap_node { \
  key_t key; \
  value_t value; \
  unsigned hash; \
  enum hmap_node_state state; \
}; \
struct pre##hmap { \
  struct pre##hmap_node *nodes; \
  struct pre##hmap_node *end; \
  int mod; \
  unsigned mask; \
  int size; \
  int cap; \
  int used; \
  unsigned (*ha)(key_t); \
  int (*eq)(key_t, key_t); \
}; \
static int closest_shift(int n) { \
  int i = 0; \
  for (; n; ++i) { \
    n >>= 1; \
  } \
  return i; \
} \
static void pre##hmap_set_shift(struct pre##hmap *hm, int shift) { \
  hm->cap = 1 << shift; \
  hm->mod = prime_mod[shift]; \
  hm->mask = hm->cap - 1; \
} \
static void pre##hmap_set_shift_from_cap(struct pre##hmap *hm, int cap) { \
  int shift = closest_shift(cap); \
  if (shift < HASH_MIN_SHIFT) { \
    shift = HASH_MIN_SHIFT; \
  } \
  pre##hmap_set_shift(hm, shift); \
} \
static void pre##hmap_setup(struct pre##hmap *hm, int shift) { \
  if (shift < HASH_MIN_SHIFT) { \
    shift = HASH_MIN_SHIFT; \
  } \
  pre##hmap_set_shift(hm, shift); \
  hm->nodes = calloc(hm->cap, sizeof(struct pre##hmap_node)); \
  hm->end = hm->nodes + hm->cap; \
} \
static void pre##hmap_realloc_arrays(struct pre##hmap *hm) { \
  hm->nodes = realloc(hm->nodes, hm->cap * sizeof(struct pre##hmap_node)); \
  hm->end = hm->nodes + hm->cap; \
} \
static void relocate_map(struct pre##hmap *hm, unsigned ocap, \
          unsigned char *reallocated_flags) { \
  for (int i = 0; i < ocap; ++i) { \
    if (hm->nodes[i].state != USING) { \
      hm->nodes[i].state = UNUSED; \
      continue; \
    } \
    if (GET_BIT(reallocated_flags, i)) { \
      continue; \
    } \
    struct pre##hmap_node n = hm->nodes[i]; \
    hm->nodes[i].state = UNUSED; \
    for (;;) { \
      unsigned idx, step = 0; \
      idx = HASH2IDX(hm, n.hash); \
      while (GET_BIT(reallocated_flags, idx)) { \
        ++step; \
        idx += step; \
        idx &= hm->mask; \
      } \
      SET_BIT(reallocated_flags, idx); \
      if (hm->nodes[idx].state != USING) { \
        hm->nodes[idx] = n; \
        break; \
      } \
      struct pre##hmap_node tmp = hm->nodes[idx]; \
      hm->nodes[idx] = n; \
      n = tmp; \
    } \
  } \
} \
static void pre##hmap_realloc(struct pre##hmap *hm) { \
  int ocap = hm->cap; \
  pre##hmap_set_shift_from_cap(hm, hm->size * 1.333); \
  if (hm->cap > ocap) { \
    pre##hmap_realloc_arrays(hm); \
    memset(hm->nodes + ocap, 0, (hm->cap - ocap) * sizeof(struct pre##hmap_node)); \
  } \
  unsigned char *reallocated_flags = calloc((hm->cap + 7) / 8, sizeof(unsigned char)); \
  relocate_map(hm, ocap, reallocated_flags); \
  free(reallocated_flags); \
  if (hm->cap < ocap) { \
    pre##hmap_realloc_arrays(hm); \
  } \
  hm->used = hm->size; \
} \
static inline int pre##hmap_maybe_realloc(struct pre##hmap *hm) { \
  unsigned used = hm->used, cap = hm->cap; \
  if ((cap > hm->size * 4 && cap > 1 << HASH_MIN_SHIFT) || \
      (cap <= used + (used/16))) { \
    pre##hmap_realloc(hm); \
    return 1; \
  } \
  return 0; \
} \
static struct pre##hmap_node *pre##hmap_rem_node(struct pre##hmap *hm, int idx) { \
  struct pre##hmap_node *n = hm->nodes + idx; \
  n->state = DELETED; \
  hm->size--; \
  return n; \
} \
static inline int pre##hmap_lookup(struct pre##hmap *hm, key_t key, \
      unsigned *hash_return) { \
  unsigned lookup_hash = hm->ha(key); \
  if (hash_return) { \
    *hash_return = lookup_hash; \
  } \
  int idx = HASH2IDX(hm, lookup_hash); \
  struct pre##hmap_node *n = hm->nodes + idx; \
  int first_deleted = -1; \
  int step = 0; \
  while (n->state != UNUSED) { \
    if (n->state == USING) { \
      if (n->hash == lookup_hash && hm->eq(n->key, key)) { \
        return idx; \
      } \
    } else if (n->state == DELETED && first_deleted < 0) { \
      first_deleted = idx; \
    } \
    ++step; \
    idx += step; \
    idx &= hm->mask; \
    n = hm->nodes + idx; \
  } \
  if (first_deleted >= 0) { \
    return first_deleted; \
  } \
  return idx; \
} \
struct pre##hmap *pre##hmap(int shift, unsigned (*ha)(), int (*eq)()) { \
  struct pre##hmap *hm = malloc(sizeof(struct pre##hmap)); \
  hm->size = 0; \
  hm->used = 0; \
  hm->ha = ha; \
  hm->eq = eq; \
  pre##hmap_setup(hm, shift); \
  return hm; \
} \
struct pre##hmap_node *pre##hmap_put(struct pre##hmap *hm, key_t k, value_t v) { \
  unsigned key_hash; \
  int idx = pre##hmap_lookup(hm, k, &key_hash); \
  struct pre##hmap_node *n = hm->nodes + idx; \
  if (n->state == USING) { \
    return n; \
  } \
  n->hash = key_hash; \
  n->key = k; \
  n->value = v; \
  ++hm->size; \
  int new_usage = n->state == UNUSED; \
  n->state = USING; \
  if (new_usage) { \
    ++hm->used; \
    pre##hmap_maybe_realloc(hm); \
  } \
  return NULL; \
} \
value_t *pre##hmap_get(struct pre##hmap *hm, key_t k) { \
  int idx = pre##hmap_lookup(hm, k, NULL); \
  struct pre##hmap_node *n = hm->nodes + idx; \
  if (n->state == USING) { \
    return &n->value; \
  } \
  return NULL; \
} \
struct pre##hmap_node *pre##hmap_rem(struct pre##hmap *hm, key_t key) { \
  int idx = pre##hmap_lookup(hm, key, NULL); \
  if (hm->nodes[idx].state != USING) { \
    return NULL; \
  } \
  pre##hmap_rem_node(hm, idx); \
  if (pre##hmap_maybe_realloc(hm)) { \
    idx = pre##hmap_lookup(hm, key, NULL); \
  } \
  return hm->nodes + idx; \
} \
void pre##hmap_del(struct pre##hmap *hm) { \
  free(hm->nodes); \
  free(hm); \
} \
struct pre##hmap_node *pre##hmap_first(struct pre##hmap *hm) {\
  for (struct pre##hmap_node *iter = hm->nodes; iter < hm->end; ++iter) { \
    if (iter->state == USING) { \
      return iter; \
    } \
  } \
  return NULL; \
} \
struct pre##hmap_node *pre##hmap_next(struct pre##hmap *hm, struct pre##hmap_node *n) { \
  ++n; \
  while (n < hm->end) { \
    if (n->state == USING) { \
      return n; \
    } \
    ++n; \
  } \
  return NULL; \
}

#define HMAP_DECL_IMPL(pre, key_t, value_t) \
HMAP_DECL(pre, key_t, value_t) \
HMAP_IMPL(pre, key_t, value_t)

static inline unsigned hash_s(const char *s) {
  register unsigned h = 5381;
  for (; *s != '\0'; ++s) {
    h = (h << 5) + h + *s;
  }
  return h;
}

static inline int eq_s(const char *s1, const char *s2) {
  for (;*s1 && *s2 && *s1 == *s2; ++s1, ++s2) {
  }
  return *s1 == *s2;
}

#endif  // HMAP_H_