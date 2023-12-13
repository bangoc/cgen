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

#endif  // TESTS_MYLIB_LIB_H_