/* (C) Nguyễn Bá Ngọc 2023 */
#ifndef TESTS_MYLIB_LIB_H_
#define TESTS_MYLIB_LIB_H_

#include "all.h"
VDECL(vectint, int, vi);

#define VMATCH(v, api) \
  _Generic((v), \
    struct vectint *: vi##api \
  )

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

#endif  // TESTS_MYLIB_LIB_H_