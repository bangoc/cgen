/* (C) Nguyễn Bá Ngọc 2023 */
#ifndef TESTS_MYLIB_LIB_H_
#define TESTS_MYLIB_LIB_H_

#include "all.h"
VDECL(vectint, int, vi);
VDECL(vectdbl, double, vd);

#define VMATCH(v, api) \
  _Generic((v), \
    struct vectint *: vi##api, \
    struct vectdbl *: vd##api \
  )

#define VCONSTRUCT(vecname, objname, size) \
  struct vecname *objname = VMATCH((struct vecname *)NULL, create)(size)
#define VRESERVE(v, ...) VMATCH(v, reserve)(v, __VA_ARGS__)
#define VRESIZE(v, ...) VMATCH(v, resize)(v, __VA_ARGS__)
#define VAPPEND(v, ...) VMATCH(v, append)(v, __VA_ARGS__)
#define VREMOVE(v, ...) VMATCH(v, remove)(v, __VA_ARGS__)
#define VINSERTB(v, ...) VMATCH(v, insertb)(v, __VA_ARGS__)
#define VCLEAR(v) VMATCH(v, clear)(v)
#define VFREE(v) VMATCH(v, free)(v)
#define VFILL(v, ...) VMATCH(v, fill)(v, __VA_ARGS__)
#define VPUSH(v, ...) VMATCH(v, push)(v, __VA_ARGS__)
#define VPOP(v) VMATCH(v, pop)(v)
#define VTOP(v) VMATCH(v, top)(v)
#define VENQUE(v, ...) VMATCH(v, enque)(v, __VA_ARGS__)
#define VPEEK(v) VMATCH(v, peek)(v)
#define VDEQUE(v, ...) VMATCH(v, deque)(v, __VA_ARGS__)

SDECL(silist, int, si);
#define SMATCH(list, api) \
  _Generic((list), \
      struct silist *: si##api \
    )

#define SCONSTRUCT(sname, objname) \
  struct sname *objname = SMATCH((struct sname *)NULL, create)()
#define SFREE(list) SMATCH(list, free)(list)
#define SAPPEND(list, ...) SMATCH(list, append)(list, __VA_ARGS__)
#define SPREPEND(list, ...) SMATCH(list, prepend)(list, __VA_ARGS__)
#define SDFRONT(list) SMATCH(list, dfront)(list)

#define SPUSH(list, elem) SPREPEND(list, elem)
#define SPOP(list) SDFRONT(list)
#define SENQUE(list, elem) SAPPEND(list, elem)
#define SDEQUE(list) SDFRONT(list)

TDECL(tsimap, char *, int, tsi);
#define TMATCH(map, api) \
  _Generic((map), \
    struct tsimap *: tsi##api \
  )
#define TNODE_MATCH(node, api) \
  _Generic((node), \
    struct tsimap_node *: tsi##api \
  )

#define TLEFT_MOST(n) TNODE_MATCH(n, left_most)(n)
#define TRIGHT_MOST(n) TNODE_MATCH(n, right_most)(n)
#define TLEFT_DEEPEST(n) TNODE_MATCH(n, left_deepest)(n)
#define TNEXT_LRN(n) TNODE_MATCH(n, next_lrn)(n)
#define TNEXT_LNR(n) TNODE_MATCH(n, next_lnr)(n)
#define TPREV_LNR(n) TNODE_MATCH(n, prev_lnr)(n)
#define TFIRST_LNR(t) TMATCH(t, first_lnr)(t)
#define TLAST_LNR(t) TMATCH(t, last_lnr)(t)
#define TCONSTRUCT(tname, objname, ...) \
  struct tname *objname = TMATCH((struct tname *)NULL, create)(__VA_ARGS__)
#define TPUT(t, k, v) TMATCH(t, put)(t, k, v)
#define TGET(t, k) TMATCH(t, get)(t, k)
#define TREMOVE(t, k) TMATCH(t, remove)(t, k)
#define TFREE(t) TMATCH(t, free)(t)

#endif  // TESTS_MYLIB_LIB_H_