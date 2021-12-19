#ifndef BASE_SLL_H_
#define BASE_SLL_H_

typedef struct sll_node_s {
  struct sll_node_s *next;
} *sll_node_t;

typedef struct sll_s {
  sll_node_t front;
  sll_node_t back;
  void (*fn)();  // Hàm giải phóng bộ nhớ cho nút
} *sll_t;

sll_node_t sll_create_node();
void sll_free_node(sll_node_t node);
sll_t sll_create_list();
void sll_free_list(sll_t list);

void sll_push_back(sll_t list, sll_node_t node);
void sll_push_front(sll_t list, sll_node_t node);
void sll_pop_front(sll_t list);
sll_node_t sll_front(sll_t list);
int sll_is_empty(sll_t list);
long sll_length(sll_t list);

void sll_pprint_node(sll_node_t node);
void sll_pprint_list(sll_t list);

#define sll_traverse(cur, list) \
  for (sll_node_t cur = list->front; cur != NULL; cur = cur->next)

#endif