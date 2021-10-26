#include "OOP/Sll.c"

int main() {
  SllG list = New(SllG);
  list->PushBack(list, (gtype){.i = 100});
  list->PushBack(list, (gtype){.i = 1});
  list->PushBack(list, (gtype){.i = 200});
  list->PushFront(list, (gtype){.i = 30});
  list->PushBack(list, (gtype){.i = 1000});
  list->PPrint(list);
  return 0;
}