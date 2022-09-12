#ifndef LIST_DLL_H_
#define LIST_DLL_H_

/* (C) Nguyen Ba Ngoc, 2021 */

/**
 * Generic double Linked List (DLL/dll)
 */

typedef struct double_linked_node {
  struct double_linked_node *next;
  struct double_linked_node *prev;
} dln_s, *dln_t;

typedef struct double_linked_list {
  dln_t front;
  dln_t back;
  long length;
} *dll_t;

typedef void (*dll_node_print_t)(dln_t);

#define dll_node(n) ((dln_t)(n))
#define dll_list(list) ((dll_t)(list))
#define dll_front(list) (dll_list(list)->front)
#define dll_back(list) (dll_list(list)->back)
#define dll_length(list) (dll_list(list)->length)

#define dll_traverse(cur, list) \
  for (dln_t cur = (list)->front; cur != NULL; cur = cur->next)

#define dll_rtraverse(cur, list) \
  for (dln_t cur = (list)->back; cur != NULL; cur = cur->prev)

#define dll_is_empty(list) \
  (dll_front(list) == NULL && dll_back(list) == NULL)

#define dll_free(list) \
  do {\
    while (!dll_is_empty(list)) { \
      dll_pop_front(list); \
    } \
    free(list); \
  } while(0)

#define dll_clear(list) \
  do {\
    while (!dll_is_empty(list)) { \
      dll_pop_front(list); \
    } \
  } while (0)

dln_t dll_create_node();
dll_t dll_create_list();
void dll_push_back(dll_t list, dln_t nn);
void dll_push_front(dll_t list, dln_t nn);
void dll_pop_front(dll_t list);
void dll_pop_back(dll_t list);
dln_t dll_inserta(dll_t list, dln_t pos, dln_t nn);
dln_t dll_insertb(dll_t list, dln_t pos, dln_t nn);
void dll_erase(dll_t list, dln_t pos);
void dll_node_print_address(dln_t);
void dll_pprint(dll_t, dll_node_print_t);

#endif  // LIST_DLL_H_
