#ifndef LIST_SLL_H_
#define LIST_SLL_H_

typedef struct single_linked_node {
  struct single_linked_node *next;
} sln_s, *sln_t;

typedef struct single_linked_list {
  sln_t front;
  sln_t back;
  long length;
} *sll_t;

typedef void (*sll_node_print_t)(sln_t);

#define sll_node(n) ((sln_t)(n))
#define sll_list(list) ((sll_t)(list))
#define sll_front(list) (sll_list(list)->front)
#define sll_back(list) (sll_list(list)->back)
#define sll_length(list) (sll_list(list)->length)

#define sll_traverse(cur, list) \
  for (sln_t cur = list->front; cur != NULL; cur = cur->next)

#define sll_free(list) \
  do { \
    while (!sll_is_empty(list)) { \
      sll_pop_front(list); \
    } \
    free(list); \
  } while (0)

#define sll_is_empty(list) \
  (sll_front(list) == NULL && sll_back(list) == NULL)

sln_t sll_create_node();
sll_t sll_create_list();
void sll_push_back(sll_t list, sln_t node);
void sll_push_front(sll_t list, sln_t node);
void sll_pop_front(sll_t list);
void sll_node_print_address(sln_t node);
void sll_pprint(sll_t list, sll_node_print_t npp);

#endif  // LIST_SLL_H_