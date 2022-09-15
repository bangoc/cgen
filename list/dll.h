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
 * dln = double linked node
 */
struct dln {
  struct dln *next;
  struct dln *prev;
};

/**
 * Cấu trúc mô tả danh sách móc nối kép
 */
struct dll {
  struct dln *front;
  struct dln *back;
  long length;
};

typedef void (*dll_node_print_t)(struct dln *);

#define dll_node(n) ((struct dln *)(n))
#define dll_list(list) ((struct dll *)(list))
#define dll_front(list) (dll_list(list)->front)
#define dll_back(list) (dll_list(list)->back)
#define dll_length(list) (dll_list(list)->length)

#define dll_traverse(cur, list) \
  for (struct dln *cur = (list)->front; cur != NULL; cur = cur->next)

#define dll_rtraverse(cur, list) \
  for (struct dln *cur = (list)->back; cur != NULL; cur = cur->prev)

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

struct dln *dll_create_node();
struct dll *dll_create_list();
void dll_push_back(struct dll *list, struct dln *nn);
void dll_push_front(struct dll *list, struct dln *nn);
void dll_pop_front(struct dll *list);
void dll_pop_back(struct dll *list);
void dll_inserta(struct dll *list, struct dln *pos, struct dln *nn);
void dll_insertb(struct dll *list, struct dln *pos, struct dln *nn);
void dll_erase(struct dll *list, struct dln *pos);
void dll_node_print_address(struct dln *);
void dll_pprint(struct dll *, dll_node_print_t);

#endif  // LIST_DLL_H_
