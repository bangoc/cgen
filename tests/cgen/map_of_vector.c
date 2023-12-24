#include "all.h"

VDECL_IMPL(ivector, int, vi);
TDECL_IMPL(svmap, char*, struct ivector *, sv);

int main() {
  struct svmap *sv = svmap(cmps);
  sv->fv = vifree;
  struct ivector *va = ivector(0);
  svput(sv, "aaa", va);
  struct ivector *vb = ivector(0);
  svput(sv, "bbb", vb);
  struct ivector *vc = ivector(0);
  svput(sv, "ccc", vc);
  viappend(va, 1);
  viappend(va, 2);
  viappend(vb, 3);
  viappend(vc, 7);
  viappend(vc, 9);
  viappend(vc, 10);
  struct TNN(svmap) *n = svfirst_lnr(sv);
  while (n) {
    printf("%s: ", n->key);
    for (int i = 0; i < n->value->size; ++i) {
      printf(" %d", n->value->elems[i]);
    }
    printf("\n");
    n = svnext_lnr(n);
  }
  svfree(sv);
}