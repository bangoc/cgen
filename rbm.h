#ifndef RBM_H_
#define RBM_H_

/* (C) 2021 Nguyen Ba Ngoc (bangoc) */

/** @file
 * @brief Ánh xạ khóa=>giá trị khái quát dựa trên cây đỏ-đen
 *
 * rbm - Red-black tree map là một triển khai ánh xạ khái quát
 * dựa trên cây đỏ đen (gọi ngắn gọn là bảng cây). Khóa và giá
 * trị được lưu trong cùng nút của cây và có kiểu ::gtype. Các
 * khóa được so sánh bằng hàm do người dùng cung cấp.
 */

#include "base/rb.h"
#include "base/gtype.h"

/**
 * \headerfile "cgen.h"
 * Cấu trúc nút của rbm, là mở rộng nút của cây đỏ đen.
 */
typedef struct rbm_node {
  struct rb_node_s rb_node;

  /** \private
   * Người sử dụng không cần trực tiếp truy cập tới
   * các thuộc tính của nút.
   */
  gtype key, value;
} *rbm_node_t;

/**
 * \headerfile "cgen.h"
 * Cấu trúc điều khiển của bảng cây rbm, được tạo bằng hàm
 * rbm_create(gtype_cmp_t cmp, gtype_free_t free_key, gtype_free_t free_value).
 *
 */
typedef struct rbm_s {
  struct bn_tree t;
  gtype_cmp_t cmp;
  gtype_free_t free_key, free_value;
} *rbm_t;

/**
 * Cấu trúc kết quả trả về của hàm rbm_insert(rbm_t t, gtype key, gtype value),
 * cho biết trạng thái kết thúc thao tác thêm dữ liệu vào rbm.
 */
typedef struct rbm_insert_result {
  gtype *value;
  int inserted;
} rbm_ires;

#define to_rbm(n) ((rbm_node_t)(n))
#define rbm_node_key(n) (to_rbm(n)->key)
#define rbm_node_value(n) (to_rbm(n)->value)

rbm_node_t rbm_create_node(gtype key, gtype value);

/**
 * Hàm tạo đối tượng điều khiển bảng cây.
 *
 * @param cmp Hàm so sánh các giá trị khóa, phải != NULL.
 * Tham khảo: gtype_cmp_s(gtype v1, gtype v2).
 * @param free_key Con trỏ tới hàm giải phóng bộ nhớ ngoài được gắn với khóa, tham khảo.
 * gtype_free_s(gtype v). Được gọi khi xóa dữ liệu nếu != NULL. Trong trường hợp không
 * có bộ nhớ ngoài hoặc không cần xóa bộ nhớ ngoài (như tình huống đang chia sẻ bộ nhớ
 * với 1 câu trúc lưu trữ khác) thì để = NULL.
 * @param free_value Con trỏ tới hàm giải phóng bộ nhớ ngoài được gắn với giá trị, tương
 * tự free_key.
 * @return Trả về đối tượng điều khiển bảng cây.
 *
 * \memberof rbm_s
 *
 * Tham khảo: hmap_create(gtype_hash_t hash_func, gtype_cmp_t cmp, gtype_free_t free_key, gtype_free_t free_value)
 */
rbm_t rbm_create(gtype_cmp_t cmp,
  gtype_free_t free_key, gtype_free_t free_value);

rbm_ires rbm_insert(rbm_t t, gtype key, gtype value);
gtype *rbm_vref(rbm_t t, gtype key);
rbm_node_t rbm_search(rbm_t t, gtype key);
int rbm_remove(rbm_t t, gtype key);

#define rbm_size(t) (bn_size((bn_tree_t)s))

#define rbm_free(m) \
  do { \
    if ((m)->free_key || (m)->free_value) { \
      rbm_traverse(_k, _v, (m)) { \
        if ((m)->free_key) { \
          (m)->free_key(*_k); \
        } \
        if ((m)->free_value) { \
          (m)->free_value(*_v); \
        } \
      } \
    } \
    bn_free_tree((bn_tree_t)(m)); \
  } while (0)

static inline void _rbm_move_next(gtype **k, gtype **v) {
  rbm_node_t nd = container_of(*k, struct rbm_node, key);
  bn_node_t tmp = bn_next_inorder(to_bn(nd));
  if (!tmp) {
    *k = NULL_PTR;
    *v = NULL_PTR;
    return;
  }
  *k = &(rbm_node_key(tmp));
  *v = &(rbm_node_value(tmp));
}

#define rbm_traverse(k, v, m) \
  for (gtype *k = &(rbm_node_key(bn_left_most((m)->t.root))), \
             *v = &(rbm_node_value(bn_left_most((m)->t.root))); \
       k != NULL_PTR && v != NULL_PTR; _rbm_move_next(&k, &v)) \

#endif  // RBM_H_
