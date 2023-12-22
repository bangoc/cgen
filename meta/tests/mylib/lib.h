/* (C) Nguyễn Bá Ngọc 2023 */
#ifndef MYLIB_LIB_H_
#define MYLIB_LIB_H_

#include "all.h"
VDECL(vectint, int, vi);
VDECL(vectdbl, double, vd);
VDECL(vectstr, char *, vs);

#define VMATCH(v, api) \
  _Generic((v), \
    struct vectint *: vi##api, \
    struct vectdbl *: vd##api, \
    struct vectstr *:vs##api \
  )

SDECL(silist, int, si);
#define SMATCH(list, api) \
  _Generic((list), \
      struct silist *: si##api \
    )

TDECL(tsimap, char *, int, tsi);
#define TMATCH(map, api) \
  _Generic((map), \
    struct tsimap *: tsi##api \
  )
#define TNODE_MATCH(node, api) \
  _Generic((node), \
    struct tsimap_node *: tsi##api \
  )

#define SFV(list) ((list)->fv)
#define SSIZE(list) ((list)->size)
#define SFRONT(list) ((list)->front->data)
#define STOP(list) SFRONT(list)
#define SPEEK(list) SFRONT(list)
#define SBACK(list) ((list)->back->data)
#define SEMPTY(list) (SSIZE(list) == 0)
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

#define VARR(v) ((v)->elems)
#define VELEM(v, i) (VARR(v)[(i)])
#define VIDXOF(pe, v) ((pe) - VARR(v))
#define VRIO(v) ((v)->rio)
#define VFV(v) ((v)->fv)
#define VSIZE(v) ((const long)((v)->size))
#define VCAP(v) ((const long)(v)->cap)
#define VLASTIDX(v) (VSIZE(v) - 1)
#define VEMPTY(v) (VSIZE(v) == 0)
#define VSORT(v, cmp) qsort(v->elems, v->size, sizeof(v->elems[0]), cmp)
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

#define VFOR(i, v) \
  for (long i = 0; i < VSIZE(v); ++i)

#define VRFOR(i, v) \
  for (long i = VLASTIDX(v); i >= 0; --i)

#define TKEY(n) ((n)->key)
#define TVALUE(n) ((n)->value)
#define TLEFT(n) ((n)->left)
#define TRIGHT(n) ((n)->right)
#define TTOP(n) ((n)->top)
#define TSIZE(t) ((t)->size)
#define TROOT(t) ((t)->root)
#define TFK(t) ((t)->fk)
#define TFV(t) ((t)->fv)
#define TLEFT_MOST(n) TNODE_MATCH(n, left_most)(n)
#define TRIGHT_MOST(n) TNODE_MATCH(n, right_most)(n)
#define TLEFT_DEEPEST(n) TNODE_MATCH(n, left_deepest)(n)
#define TNEXT_LRN(n) TNODE_MATCH(n, next_lrn)(n)
#define TNEXT_LNR(n) TNODE_MATCH(n, next_lnr)(n)
#define TPREV_LNR(n) TNODE_MATCH(n, prev_lnr)(n)
#define TFIRST_LRN(t) TMATCH(t, first_lrn)(t)
#define TFIRST_LNR(t) TMATCH(t, first_lnr)(t)
#define TLAST_LNR(t) TMATCH(t, last_lnr)(t)
#define TCONSTRUCT(tname, objname, ...) \
  struct tname *objname = TMATCH((struct tname *)NULL, create)(__VA_ARGS__)
#define TPUT(t, k, v) TMATCH(t, put)(t, k, v)
#define TGET(t, k) TMATCH(t, get)(t, k)
#define TREMOVE(t, k) TMATCH(t, remove)(t, k)
#define TFREE(t) TMATCH(t, free)(t)

#endif  // MYLIB_LIB_H_