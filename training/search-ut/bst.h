#ifndef BST_INT_H_
#define BST_INT_H_

struct bst_node;
struct bst_tree;

struct bst_node *bst_node(int key);
struct bst_tree *bst_tree();
struct bst_node *bst_put(struct bst_tree *t, int key);
struct bst_node *bst_search(struct bst_tree *t, int key);
void bst_free(struct bst_tree *t);
struct bst_node *bst_first_lnr(struct bst_tree *t);
struct bst_node *bst_next_lnr(struct bst_node *n);

#endif  // BST_INT_H_