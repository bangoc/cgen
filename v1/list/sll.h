#ifndef LIST_SLL_H_
#define LIST_SLL_H_

/* (C) Nguyen Ba Ngoc 2021 */

/** @file
 * @brief Triển khai khái quát danh sách móc nối đơn chỉ bao gồm
 * cấu trúc liên kết.
 * Có thể kế thừa để lưu dữ liệu trong các nút.
 *
 */

/**
 * Cấu trúc mô tả nút của danh sách móc nối đơn
 * slnode = single linked node
 */
struct slnode {
  struct slnode *next;
};

/**
 * Cấu trúc mô tả danh sách móc nối đơn
 * sll = single linked list
 */
struct sllist {
  struct slnode *front;
  struct slnode *back;
  long length;
};

typedef void (*sll_node_print_t)(struct slnode *);

#define sll_node(n) ((struct slnode *)(n))
#define sll_list(list) ((struct sllist *)(list))
#define sll_front(list) (sll_list(list)->front)
#define sll_back(list) (sll_list(list)->back)
#define sll_length(list) (sll_list(list)->length)

#define sll_traverse(cur, list) \
  for (struct slnode *cur = sll_front(list); cur != NULL; cur = cur->next)

#define sll_free(list) \
  do { \
    while (!sll_is_empty(list)) { \
      sll_pop_front(list); \
    } \
    free(list); \
  } while (0)

#define sll_is_empty(list) \
  (sll_front(list) == NULL && sll_back(list) == NULL)

struct slnode *sll_create_node();
struct sllist *sll_create_list();

void __sll_push_back(struct sllist *list, struct slnode *node);
#define sll_push_back(list, nn) __sll_push_back(sll_list(list), nn)

void __sll_push_front(struct sllist *list, struct slnode *node);
#define sll_push_front(list, nn) __sll_push_front(sll_list(list), nn)

void __sll_inserta(struct sllist *list, struct slnode *pos, struct slnode *nn);
#define sll_inserta(list, pos, nn) __sll_inserta(sll_list(list), pos, nn)

void __sll_pop_front(struct sllist *list);
#define sll_pop_front(list) __sll_pop_front(sll_list(list))

void sll_node_print_address(struct slnode *node);
void sll_pprint(struct sllist *list, sll_node_print_t npp);

#endif  // LIST_SLL_H_