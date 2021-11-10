/*
  first reported by Lê Văn Duẩn
*/
#include "s2i.h"

#include <stdio.h>

bn_tree_t s2i = NULL; //cay chua string -> int
int g_id = 0;


int main(){
  s2i = bn_create_tree(NULL_PTR);

  s2i_insert(s2i,"aa",1);
  s2i_insert(s2i,"bb",2);
  s2i_insert(s2i,"cc",3);
  s2i_insert(s2i,"dd",4);
  s2i_delete(s2i, "bb");
  s2i_delete(s2i, "cc");
  s2i_free(s2i); //giai phong bo nho cho cay s2i
  return 0;
}