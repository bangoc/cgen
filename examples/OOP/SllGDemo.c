#include "OOP/Sll.c"

int main() {
  SllGt list = New(SllGt);
  list->PushBack(list, gtype_l(100));
  list->PushBack(list, gtype_l(1));
  list->PushBack(list, gtype_l(200));
  list->PushFront(list, gtype_l(30));
  list->PushBack(list, gtype_l(1000));
  list->Foreach(list, gtype_print_l);
  Delete(SllGt, list);
  return 0;
}