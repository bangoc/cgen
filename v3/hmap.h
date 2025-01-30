/* (C) Nguyễn Bá Ngọc 2024-2025 */
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
struct hname##_node; \
struct hname; \
struct hname *hname(int cap, unsigned (*ha)(), int (*eq)()); \
struct hname##_node *hname##_put(struct hname *hm, key_t k, value_t v); \
value_t *hname##_get(struct hname *hm, key_t k); \
int hname##_rem(struct hname *hm, key_t k); \
void hname##_free(struct hname *hm);

#define HMAP_IMPL(hname, key_t, value_t) \
struct hname##_node { \
  key_t key; \
  value_t value; \
  unsigned hash; \
  enum hmap_node_state state; \
}; \
struct hname { \
  struct hname##_node *nodes; \
  struct hname##_node *end; \
  int mod; \
  unsigned mask; \
  int size; \
  int cap; \
  int used; \
  unsigned (*ha)(key_t); \
  int (*eq)(key_t, key_t); \
  void (*fk)(); \
  void (*fv)(); \
}; \
static int closest_shift(int n) { \
  int i = 0; \
  for (; n; ++i) { \
    n >>= 1; \
  } \
  return i; \
} \
static void hname##_set_shift(struct hname *hm, int shift) { \
  hm->cap = 1 << shift; \
  hm->mod = prime_mod[shift]; \
  hm->mask = hm->cap - 1; \
} \
static void hname##_set_shift_from_cap(struct hname *hm, int cap) { \
  int shift = closest_shift(cap); \
  if (shift < HASH_MIN_SHIFT) { \
    shift = HASH_MIN_SHIFT; \
  } \
  hname##_set_shift(hm, shift); \
} \
static void hname##_setup(struct hname *hm, int shift) { \
  if (shift < HASH_MIN_SHIFT) { \
    shift = HASH_MIN_SHIFT; \
  } \
  hname##_set_shift(hm, shift); \
  hm->nodes = calloc(hm->cap, sizeof(struct hname##_node)); \
  hm->end = hm->nodes + hm->cap; \
} \
static void hname##_realloc_arrays(struct hname *hm) { \
  hm->nodes = realloc(hm->nodes, hm->cap * sizeof(struct hname##_node)); \
  hm->end = hm->nodes + hm->cap; \
} \
static void relocate_map(struct hname *hm, unsigned ocap, \
          unsigned char *reallocated_flags) { \
  for (int i = 0; i < ocap; ++i) { \
    if (hm->nodes[i].state != USING) { \
      hm->nodes[i].state = UNUSED; \
      continue; \
    } \
    if (GET_BIT(reallocated_flags, i)) { \
      continue; \
    } \
    struct hname##_node n = hm->nodes[i]; \
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
      struct hname##_node tmp = hm->nodes[idx]; \
      hm->nodes[idx] = n; \
      n = tmp; \
    } \
  } \
} \
static void hname##_realloc(struct hname *hm) { \
  int ocap = hm->cap; \
  hname##_set_shift_from_cap(hm, hm->size * 1.333); \
  if (hm->cap > ocap) { \
    hname##_realloc_arrays(hm); \
    memset(hm->nodes + ocap, 0, (hm->cap - ocap) * sizeof(struct hname##_node)); \
  } \
  unsigned char *reallocated_flags = calloc((hm->cap + 7) / 8, sizeof(unsigned char)); \
  relocate_map(hm, ocap, reallocated_flags); \
  free(reallocated_flags); \
  if (hm->cap < ocap) { \
    hname##_realloc_arrays(hm); \
  } \
  hm->used = hm->size; \
} \
static inline int hname##_maybe_realloc(struct hname *hm) { \
  unsigned used = hm->used, cap = hm->cap; \
  if ((cap > hm->size * 4 && cap > 1 << HASH_MIN_SHIFT) || \
      (cap <= used + (used/16))) { \
    hname##_realloc(hm); \
    return 1; \
  } \
  return 0; \
} \
static struct hname##_node *hname##_rem_node(struct hname *hm, int idx) { \
  struct hname##_node *n = hm->nodes + idx; \
  if (hm->fk) { \
    hm->fk(n->key); \
  } \
  if (hm->fv) { \
    hm->fv(n->value); \
  } \
  n->state = DELETED; \
  hm->size--; \
  return n; \
} \
static inline int hname##_lookup(struct hname *hm, key_t key, \
      unsigned *hash_return) { \
  unsigned lookup_hash = hm->ha(key); \
  if (hash_return) { \
    *hash_return = lookup_hash; \
  } \
  int idx = HASH2IDX(hm, lookup_hash); \
  struct hname##_node *n = hm->nodes + idx; \
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
struct hname *hname(int shift, unsigned (*ha)(), int (*eq)()) { \
  struct hname *hm = malloc(sizeof(struct hname)); \
  hm->size = 0; \
  hm->used = 0; \
  hm->ha = ha; \
  hm->eq = eq; \
  hname##_setup(hm, shift); \
  return hm; \
} \
struct hname##_node *hname##_put(struct hname *hm, key_t k, value_t v) { \
  unsigned key_hash; \
  int idx = hname##_lookup(hm, k, &key_hash); \
  struct hname##_node *n = hm->nodes + idx; \
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
    hname##_maybe_realloc(hm); \
  } \
  return NULL; \
} \
value_t *hname##_get(struct hname *hm, key_t k) { \
  int idx = hname##_lookup(hm, k, NULL); \
  struct hname##_node *n = hm->nodes + idx; \
  if (n->state == USING) { \
    return &n->value; \
  } \
  return NULL; \
} \
int hname##_rem(struct hname *hm, key_t key) { \
  int idx = hname##_lookup(hm, key, NULL); \
  if (hm->nodes[idx].state != USING) { \
    return 0; \
  } \
  hname##_rem_node(hm, idx); \
  if (hname##_maybe_realloc(hm)) { \
    idx = hname##_lookup(hm, key, NULL); \
  } \
  return 1; \
} \
void hname##_free(struct hname *hm) { \
  for (struct hname##_node *iter = hm->nodes; iter < hm->end; ++iter) { \
    if (iter->state == USING) { \
      if (hm->fk) { \
        hm->fk(iter->key); \
      } \
      if (hm->fv) { \
        hm->fv(iter->value); \
      } \
    } \
  } \
  free(hm->nodes); \
  free(hm); \
} \
struct hname##_node *hname##_first(struct hname *hm) {\
  for (struct hname##_node *iter = hm->nodes; iter < hm->end; ++iter) { \
    if (iter->state == USING) { \
      return iter; \
    } \
  } \
  return NULL; \
} \
struct hname##_node *hname##_next(struct hname *hm, struct hname##_node *n) { \
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