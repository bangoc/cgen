/*
  first reported by Lê Văn Duẩn
*/
#include "spec/s2i.h"

#include <stdio.h>

rbm_t si = NULL; //cay chua string -> int
int g_id = 0;


int main(){
  si = s2i_create_map(DUP_NO);

  s2i_put(si, "aa",1);
  s2i_put(si, "bb",2);
  s2i_put(si, "cc",3);
  s2i_put(si, "dd",4);
  s2i_remove(si, "bb");
  s2i_remove(si, "cc");
  s2i_free(si);
  return 0;
}