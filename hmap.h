#ifndef HMAP_H_
#define HMAP_H_

/* (C) Nguyen Ba Ngoc 2021 */

/** @file
 * @brief Bảng băm khái quát với khóa & giá trị kểu ::gtype
 *
 * Bảng băm là 1 dạng ánh xạ khóa => giá trị dựa trên hàm băm.
 * Trong triển khai này dữ liệu được lưu trong 1 mảng cấp phát
 * động. Xung đột chỉ số (khi 2 khóa khác nhau được quy chiếu
 * về cùng 1 chỉ số) trong triển khai này được xử lý theo cơ chế
 * địa chỉ mở (Open addressing).
 */

#include "base/arr.h"
#include "base/gtype.h"
#include "base/hashes.h"

#include <stdint.h>

/**
 * \headerfile "cgen.h"
 * Cấu trúc điều khiển đối tượng bảng băm.
 *
 * Các macro hỗ trợ:
 *   #hmap_traverse(k, v, map) - Duyệt tuần tự các cặp trong map.
 *
 */
typedef struct hash_map_s {
  int capacity;
  int mod;
  uint mask;
  int size;
  int noccupied;
  arr_t(gtype) keys;
  arr_t(gtype) values;
  arr_t(uint) hashes;
  gtype_hash_t hash_func;
  gtype_cmp_t cmp;
  gtype_free_t key_free;
  gtype_free_t value_free;
} *hmap_t;

/**
 * \headerfile "cgen.h"
 * Kiểu trả về của hàm <hmap_insert>"()"
 */
typedef struct hmap_insert_result {
  /**
   * Con trỏ tới giá trị đang được lưu trong bảng băm.
   */
  gtype *value;

  /**
   * Trạng thái: <br>
   *    = 1 Nếu đã thêm vào, <br>
   *    = 0 Nếu khóa đã tồn tại nên chưa được thêm vào.
   */
  int inserted;
} hmap_ires;

#define hmap_hash_at(map, idx) (elem_ref((map)->hashes, idx))
#define hmap_key_at(map, idx) (elem_ref((map)->keys, idx))
#define hmap_value_at(map, idx) (elem_ref((map)->values, idx))

/**
 * Hàm tạo đối tượng bảng băm.
 *
 * @param hash_func Hàm băm khóa, phải != NULL.
 * @param cmp Hàm so sánh khóa, phải != NULL.
 * @param key_free Hàm giải phóng bộ nhớ động bên ngoài được gắn với khóa.
 * Có thể == NULL nếu không có bộ nhớ ngoài.
 * @param value_free Hàm giải phóng bộ nhớ động bên ngoài được gắn với khóa.
 * Có thể == NULL nếu không có bộ nhớ ngoài.
 * @return Con trỏ tới đối tượng bảng băm được tạo. (Hiện chưa xử lý kịch)
 * bản lỗi cấp phát bộ nhớ.
 *
 * \memberof hash_map_s
 */
hmap_t hmap_create(gtype_hash_t hash_func, gtype_cmp_t cmp,
          gtype_free_t key_free, gtype_free_t value_free);

/**
 * Thêm cặp (key, value) vào bảng tab. Nếu key đã tồn tại thì
 * bỏ qua, có thể truy cập giá trị gắn với khóa đã có trong
 * bảng băm theo đối tượng ::hmap_ires được trả về.
 *
 * @param tab Con trỏ tới bảng băm
 * @param key Khóa
 * @param value Giá trị
 * @return Trả về đối tượng ::hmap_ires
 *
 * \memberof hash_map_s
 */
hmap_ires hmap_insert(hmap_t tab, gtype key, gtype value);

/**
 * Tra cứu giá trị trong bảng tab theo key.
 *
 * @param tab Con trỏ tới bảng băm.
 * @param key Khóa
 * @return Trả về con trỏ tới giá trị đang được gắn với key trong tab
 * nếu tồn tại, hoặc NULL nếu ngược lại.
 *
 * \memberof hash_map_s
 */
gtype *hmap_value(hmap_t tab, gtype key);

/**
 * Nếu key không có trong tab thì không làm gì, nếu ngược lại thì xóa cặp
 * khóa & giá trị tương ứng trong tab. Các hàm free_key và free_value được
 * gọi nếu != NULL.
 *
 * @param tab Con trỏ tới bảng băm
 * @param key Khóa cần xóa.
 * @return 1 nếu tồn tại khóa, 0 nếu ngược lại.
 *
 * \memberof hash_map_s
 */
int hmap_remove(hmap_t tab, gtype key);
void hmap_clear(hmap_t tab);

/**
 * Giải phóng bộ nhớ được cấp phát cho bảng băm tab. Các hàm free_key và
 * free_value được gọi cho từng khóa và từng giá trị nếu != NULL.
 *
 * @param tab Con trỏ tới bảng băm.
 * @return Hàm không trả về giá trị.
 *
 * \memberof hash_map_s
 */
void hmap_free(hmap_t tab);

/**
 * Số lượng cặp khóa & giá trị đang được lưu trong hmap.
 *
 * @param tab Con trỏ tới đối tượng bảng băm.
 * @return Trả về số lượng cặp khóa/giá trị đang được lưu trong tab.
 *
 */
#define hmap_size(tab) (tab->size)

gtype *hmap_next_pkey(hmap_t, gtype*);
gtype *hmap_next_pvalue(hmap_t, gtype*);

/**
 * Duyệt tuần tự các cặp khóa và giá trị trong map. Các tham số key và value
 * là các định danh do người sử dụng tự đặt và sẽ có kiểu ::gtype *
 *
 * @param key Định danh sẽ được sử dụng như con trỏ tới khóa.
 * @param value Định danh sẽ được sử dụng như giá trị tới khóa.
 * @param map Con trỏ tới bảng băm.
 */
#define hmap_traverse(key, value, map) \
  for(gtype *key = hmap_next_pkey(map, NULL), *value = hmap_next_pvalue(map, NULL); \
     key && value; key = hmap_next_pkey(map, key), value = hmap_next_pvalue(map, value)) \

#endif  // HMAP_H_