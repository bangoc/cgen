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
 *
 * \private Người sử dụng không cần thao tác với kiểu này.
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
 * Các macro hỗ trợ: <br>
 *   #rbm_size(t) - Kích thước của t.
 *   #rbm_traverse(k, v, t) - Duyệt tuần tự các cặp trong t.
 */
typedef struct rbm_s {
  struct bn_tree t;
  gtype_cmp_t cmp;
  gtype_free_t free_key;
  gtype_free_t free_value;
  long size;
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

/**
 * Thêm cặp (key, value) vào bảng t. Nếu key đã tồn tại thì
 * bỏ qua, có thể truy cập giá trị đang được gắn với khóa
 * đã có trong t bằng con trỏ ::rbm_ires::value trong kết quả
 * được trả về.
 *
 * @param t Con trỏ tới bảng cây.
 * @param key Khóa được thêm vào.
 * @param value Giá trị được thêm vào.
 * @return Trả về đối tượng ::rbm_ires
 *
 * \memberof rbm_s
 *
 * Tham khảo: hmap_insert(hmap_t tab, gtype key, gtype value)
 */
rbm_ires rbm_insert(rbm_t t, gtype key, gtype value);

/**
 * Tra cứu giá trị trong t theo key.
 *
 * @param t Con trỏ tới đối tượng bảng cây.
 * @param key Khóa được sử dụng để tìm kiếm.
 * @return Trả về con trỏ tới giá trị đang được gắn với key trong t
 * nếu tồn tại, hoặc NULL nếu ngược lại.
 *
 * \memberof rbm_s
 *
 * Tham khảo: hmap_value(hmap_t tab, gtype key)
 */
gtype *rbm_value(rbm_t t, gtype key);

/**
 * Có thể sẽ xóa hàm này.
 * \private
 */
rbm_node_t rbm_search(rbm_t t, gtype key);

/**
 * Nếu key không có trong t thì bỏ qua, nếu ngược lại thì xóa cặp
 * khóa & giá trị tương ứng trong t. Các hàm free_key và free_value
 * được gọi nếu != NULL.
 *
 * @param t Con trỏ tới bảng cây.
 * @param key Khóa cần xóa.
 * @return 1 Nếu tồn tại khóa sau khi xóa dữ liệu, 0 nếu ngược lại.
 *
 * \memberof rbm_s
 *
 * Tham khảo: hmap_remove(hmap_t tab, gtype key)
 */
int rbm_remove(rbm_t t, gtype key);

/**
 * Số lượng cặp khóa & giá trị đang được lưu trong bảng.
 *
 * @param t Con trỏ tới đối tượng bảng cây.
 * @return Trả về số lượng cặp khóa/giá trị đang được lưu trong t.
 *
 */
#define rbm_size(t) ((t)->size)

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

/**
 * Duyệt tuần tự các cặp khóa & giá trị trong bảng map. Các tham số k và v
 * là các định danh do người sử dụng tự đặt và sẽ có kiểu ::gtype *
 *
 * @param k Định danh sẽ được sử dụng như con trỏ tới khóa hiện hành.
 * @param v Định danh sẽ được sử dụng như con trỏ tới giá trị hiện hành.
 * @param map Con trỏ tới bảng cây.
 *
 * Tham khảo: #hmap_traverse(key, value, map)
 */
#define rbm_traverse(k, v, map) \
  for (gtype *k = (rbm_size(map))? &(rbm_node_key(bn_left_most((map)->t.root))): NULL_PTR, \
             *v = (rbm_size(map))? &(rbm_node_value(bn_left_most((map)->t.root))): NULL_PTR; \
       k != NULL_PTR && v != NULL_PTR; _rbm_move_next(&k, &v)) \

/**
 * Giải phóng bộ nhớ được cấp phát cho bảng m. Các hàm free_key và
 * free_value được gọi cho từng khóa và giá trị nếu != NULL.
 *
 * @param map Con trỏ tới bảng cây.
 */
#define rbm_free(map) \
  do { \
    if ((map)->free_key || (map)->free_value) { \
      rbm_traverse(_k, _v, (map)) { \
        if ((map)->free_key) { \
          (map)->free_key(*_k); \
        } \
        if ((map)->free_value) { \
          (map)->free_value(*_v); \
        } \
      } \
    } \
    bn_free_tree((bn_tree_t)(map)); \
  } while (0)

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng rbm
 * đang được lưu trong 1 cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang lưu con trỏ tới đối tượng rbm.
 * Con trỏ value.v trước tiên được ép kiểu thành hmap_t, sau đó con
 * trỏ hmap_t được truyền cho hmap_free.
 * @return Hàm không trả về giá trị.
 */
void rbm_gtype_free(gtype value);

#endif  // RBM_H_
