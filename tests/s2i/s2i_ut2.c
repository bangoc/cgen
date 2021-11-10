/*
  first reported by Lê Văn Duẩn
*/
#include "s2i.h"

#include <stdio.h>

s2i_t si = NULL; //cay chua string -> int
int g_id = 0;


int main(){
  si = s2i_create();

  s2i_insert(si, "aa",1);
  s2i_insert(si, "bb",2);
  s2i_insert(si, "cc",3);
  s2i_insert(si, "dd",4);
  s2i_delete(si, "bb");
  s2i_delete(si, "cc");
  s2i_free(si);
  return 0;
}