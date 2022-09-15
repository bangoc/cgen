#ifndef LIST_DLL_H_
#define LIST_DLL_H_

/* (C) Nguyen Ba Ngoc, 2021 */

/** @file
 * @brief Triển khai danh sách móc nối kép chỉ bao gồm cấu trúc liên kết.
 * Có thể kế thừa triển khai này để tạo danh sách chứa dữ liệu trong các nút.
 * Generic double Linked List (DLL/dll)
 */

/**
 * Cấu trúc mô tả nút của danh sách móc nối kép.
 * dlnode = double linked node
 */
struct dlnode {
  struct dlnode *next;
  struct dlnode *prev;
};

/**
 * Cấu trúc mô tả danh sách móc nối kép
 * dllist = double linked list
 */
struct dllist {
  struct dlnode *front;
  struct dlnode *back;
  long length;
};

typedef void (*dll_node_print_t)(struct dlnode *);

#define dll_node(n) ((struct dlnode *)(n))
#define dll_list(list) ((struct dllist *)(list))
#define dll_front(list) (dll_list(list)->front)
#define dll_back(list) (dll_list(list)->back)
#define dll_length(list) (dll_list(list)->length)

#define dll_traverse(cur, list) \
  for (struct dlnode *cur = (list)->front; cur != NULL; cur = cur->next)

#define dll_rtraverse(cur, list) \
  for (struct dlnode *cur = (list)->back; cur != NULL; cur = cur->prev)

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

struct dlnode *dll_create_node();
struct dllist *dll_create_list();
void dll_push_back(struct dllist *list, struct dlnode *nn);
void dll_push_front(struct dllist *list, struct dlnode *nn);
void dll_pop_front(struct dllist *list);
void dll_pop_back(struct dllist *list);
void dll_inserta(struct dllist *list, struct dlnode *pos, struct dlnode *nn);
void dll_insertb(struct dllist *list, struct dlnode *pos, struct dlnode *nn);
void dll_erase(struct dllist *list, struct dlnode *pos);
void dll_node_print_address(struct dlnode *);
void dll_pprint(struct dllist *, dll_node_print_t);

#endif  // LIST_DLL_H_
