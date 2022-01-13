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
 */
typedef struct hash_map_s {
  int size;
  int mod;
  uint mask;
  int nnodes;
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
gtype *hmap_value(hmap_t tab, gtype key);
int hmap_remove(hmap_t tab, gtype key);
void hmap_clear(hmap_t tab);
void hmap_free(hmap_t tab);
int hmap_nnodes(hmap_t tab);

gtype *hmap_next_pkey(hmap_t, gtype*);
gtype *hmap_next_pvalue(hmap_t, gtype*);
#define hmap_traverse(key, value, map) \
  for(gtype *key = hmap_next_pkey(map, NULL), *value = hmap_next_pvalue(map, NULL); \
     key && value; key = hmap_next_pkey(map, key), value = hmap_next_pvalue(map, value)) \

#endif  // HMAP_H_