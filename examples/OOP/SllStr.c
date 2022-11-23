#include "OOP/cgen.ic"

gtype gtype_str(const char *str) {
  return gtype_s(ext_strdup(str));
}

int print_s(gtype value) {
  printf("%s\n", value.s);
  return 0;
}

int free_s(gtype value) {
  ext_free(value.s);
  return 0;
}

int main(int argc, char *argv[]) {
  GC_INIT();
  SllGt list = New(SllGt);
  list->PushBack(list, gtype_str("Trời ươm nắng cho mầy hồng"));
  list->PushBack(list, gtype_str("Mây qua mau em nghiêng sầu"));
  list->PushBack(list, gtype_str("..."));
  list->Foreach(list, print_s);
  list->Foreach(list, free_s);
  Delete(SllGt, list);
  return 0;
}