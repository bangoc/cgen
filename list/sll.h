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
 * sln = single linked node
 */
struct sln {
  struct sln *next;
};

/**
 * Cấu trúc mô tả danh sách móc nối đơn
 * sll = single linked list
 */
struct sll {
  struct sln *front;
  struct sln *back;
  long length;
};

typedef void (*sll_node_print_t)(struct sln *);

#define sll_node(n) ((struct sln *)(n))
#define sll_list(list) ((struct sll *)(list))
#define sll_front(list) (sll_list(list)->front)
#define sll_back(list) (sll_list(list)->back)
#define sll_length(list) (sll_list(list)->length)

#define sll_traverse(cur, list) \
  for (struct sln *cur = list->front; cur != NULL; cur = cur->next)

#define sll_free(list) \
  do { \
    while (!sll_is_empty(list)) { \
      sll_pop_front(list); \
    } \
    free(list); \
  } while (0)

#define sll_is_empty(list) \
  (sll_front(list) == NULL && sll_back(list) == NULL)

struct sln *sll_create_node();
struct sll *sll_create_list();
void sll_push_back(struct sll *list, struct sln *node);
void sll_push_front(struct sll *list, struct sln *node);
void sll_inserta(struct sll *list, struct sln *pos, struct sln *nn);
void sll_pop_front(struct sll *list);
void sll_node_print_address(struct sln *node);
void sll_pprint(struct sll *list, sll_node_print_t npp);

#endif  // LIST_SLL_H_