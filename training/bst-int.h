#ifndef BST_INT_H_
#define BST_INT_H_

struct bst_node;
struct bst_tree;

struct bst_node *bst_node(int key);
struct bst_tree *bst_tree();
struct bst_node *bst_put(struct bst_tree *t, int key);
struct bst_node *bst_search(struct bst_tree *t, int key);
int bst_equal(struct bst_tree *t1, struct bst_tree *t2);
int bst_remove(struct bst_tree *t, int key);
void bst_pprint(struct bst_tree *t);
void bst_free(struct bst_tree *t);

#endif  // BST_INT_H_