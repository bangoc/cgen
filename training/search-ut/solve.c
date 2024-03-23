struct bst_node *bst_search(struct bst_tree *t, int key) {
  struct bst_node *u = t->root;
  while (u) {
    if (key == u->key) {
      return u;
    }
    u = key < u->key ? u->left: u->right;
  }
  return NULL;
}