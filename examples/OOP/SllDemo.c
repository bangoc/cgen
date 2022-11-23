#include "OOP/Sll.c"

int main(int argc, char *argv[]) {
#ifdef CGEN_USE_GC
  GC_INIT();
#endif  // CGEN_USE_GC
  Sll list = New(Sll);
  SllNode n1 = New(SllNode);
  list->PushBack(list, n1);
  list->PPrint(list);
  Delete(Sll, list);
  return 0;
}