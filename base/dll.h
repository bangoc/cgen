#ifndef BASE_DLL_H_
#define BASE_DLL_H_

/*
  (c) Nguyen Ba Ngoc, 2021
  Generic double Linked List (DLL/dll)
*/

typedef struct dln_s {
  struct dln_s *next;
  struct dln_s *prev;
} *dln_t;

typedef struct dll_s {
  dln_t front;
  dln_t back;
} *dll_t;

#define to_dln(n) ((dln_t)n)
#define to_dll(list) ((dll_t)list)

#define dll_traverse(cur, list) \
  for (dln_t cur = list->front; cur != NULL; cur = cur->next)

#define dll_rtraverse(cur, list) \
  for (dln_t cur = list->back; cur != NULL; cur = cur->prev)

/* Giao diện khái quát */

dln_t dln_create();
dll_t dll_create();
void dll_free(dll_t list);

void dll_push_back(dll_t list, dln_t nn);
void dll_push_front(dll_t list, dln_t nn);
void dll_pop_front(dll_t list);
void dll_pop_back(dll_t list);
dln_t dll_front(dll_t list);
dln_t dll_back(dll_t list);
dln_t dll_inserta(dll_t list, dln_t pos, dln_t nn);
dln_t dll_insertb(dll_t list, dln_t pos, dln_t nn);
int dll_is_empty(dll_t list);
long dll_length(dll_t list);
void dll_erase(dll_t list, dln_t pos);
void dll_clear(dll_t list);

void dln_pprint(dln_t);
void dll_pprint(dll_t);
#define dln_free(n) free(n)

#endif  // BASE_DLL_H_
