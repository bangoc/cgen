/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

/**
 * Ánh xạ chuỗi => số (đóng gói cây đỏ-đen)
 */

#ifndef TREE_SPEC_S2I_H_
#define TREE_SPEC_S2I_H_

#include "tree/rbm.h"

#include <stdio.h>

struct rbmtree *s2i_create();


struct rbm_ires s2i_insert(struct rbmtree *si, const char *key, long value);

/**
 * Lưu cặp key & value, bỏ qua nếu key đã tồn tại.
 * Mặc định tạo bản sao của khóa
 *
 * @param si Con trỏ tới bảng cây
 * @param key Chuỗi khóa
 * @param value Mã số được gắn với khóa
 * @return NULL nếu key chưa tồn tại
 *         Con trỏ tới value nếu ngược lại.
 */
long *s2i_put(struct rbmtree *si, const char *key, long value);

/**
 * Đọc giá trị được gắn với key
 *
 * @param si Con trỏ tới bảng cây
 * @param key Chuỗi khóa
 * @return NULL nếu key chưa tồn tại
 *         Con trỏ tới value nếu ngược lại.
 */
long *s2i_value(struct rbmtree *si, const char *key);
int s2i_remove(struct rbmtree *si, const char *key);
void s2i_print_node(struct bnnode *n);

#define s2i_node_key(n) (rbm_node(n)->key)
#define s2i_node_value(n) (rbm_node(n)->value)

#define s2i_free(si) rbm_free(si)

#endif  // TREE_SPEC_S2I_H_
