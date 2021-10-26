#include "OOP/Sll.c"

int main() {
  Sll list = New(Sll);
  SllNode n1 = New(SllNode);
  list->PushBack(list, n1);
  Delete(Sll, list);
  list->PPrint(list);
  return 0;
}