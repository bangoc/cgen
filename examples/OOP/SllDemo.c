#include "OOP/Sll.c"

int main(int argc, char *argv[]) {
  GC_INIT();
  Sll list = New(Sll);
  SllNode n1 = New(SllNode);
  list->PushBack(list, n1);
  list->PPrint(list);
  Delete(Sll, list);
  return 0;
}