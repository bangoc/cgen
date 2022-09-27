#ifndef VEC_HMAP_H_
#define VEC_HMAP_H_

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

#include "base/gtype.h"
#include "base/hashes.h"
#include "vec/arr.h"

#include <stdint.h>

/**
 * \headerfile "all.h"
 * Cấu trúc điều khiển đối tượng bảng băm. Được tạo bằng hàm
 * hmap_create(gtype_hash_t hash_func, gtype_cmp_t cmp, gtype_free_t free_key, gtype_free_t free_value)
 *
 * Các macro hỗ trợ:
 *   #hmap_size(map) - Kích thước của map
 *
 *   #hmap_traverse(k, v, map) - Duyệt tuần tự các cặp trong map.
 *
 *   #hmap_free(map) - Giải phóng bộ nhớ của map
 *
 */
struct hmap {
  int capacity;
  int mod;
  uint mask;
  int size;
  int noccupied;
  atype(gtype) *keys;
  atype(gtype) *values;
  atype(uint) *hashes;
  gtype_hash_t hash_func;
  gtype_cmp_t cmp;
  gtype_free_t free_key;
  gtype_free_t free_value;
};

/**
 * \headerfile "all.h"
 * Kiểu trả về của hàm hmap_insert(struct hmap *tab, gtype key, gtype value)
 */
struct hmap_ires {
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
};

#define hmap_hash_at(map, idx) ((map)->hashes[(idx)])
#define hmap_key_at(map, idx) ((map)->keys[(idx)])
#define hmap_value_at(map, idx) ((map)->values[(idx)])

/**
 * Hàm tạo đối tượng bảng băm.
 *
 * @param hash_func Hàm băm khóa, phải != NULL.
 * Tham khảo: gtype_cmp_s(gtype v1, gtype v2).
 * @param cmp Hàm so sánh khóa, phải != NULL.
 * @param free_key Hàm giải phóng bộ nhớ động bên ngoài được gắn với khóa.
 * Được gọi khi xóa dữ liệu nếu != NULL. Trong trường hợp không
 * có bộ nhớ ngoài hoặc không cần xóa bộ nhớ ngoài (như tình huống đang chia sẻ bộ nhớ
 * với 1 câu trúc lưu trữ khác) thì để = NULL.
 * @param free_value Hàm giải phóng bộ nhớ động bên ngoài được gắn với giá trị.
 * Tương tự free_key.
 * @return Con trỏ tới đối tượng bảng băm được tạo. (Hiện chưa xử lý kịch)
 * bản lỗi cấp phát bộ nhớ.
 *
 * \memberof hmap
 *
 * Tham khảo: rbm_create(gtype_cmp_t cmp, gtype_free_t free_key, gtype_free_t free_value)
 */
struct hmap *hmap_create(gtype_hash_t hash_func, gtype_cmp_t cmp,
          gtype_free_t free_key, gtype_free_t free_value);

/**
 * Thêm cặp (key, value) vào bảng tab. Nếu key đã tồn tại thì
 * bỏ qua, có thể truy cập giá trị đang được gắn với khóa đã có
 * trong bảng băm bằng con trỏ ::struct hmap_ires::value trong kết quả
 * được trả về.
 *
 * @param tab Con trỏ tới bảng băm
 * @param key Khóa được thêm vào
 * @param value Giá trị giá trị được thêm vào
 * @return Trả về đối tượng ::struct hmap_ires
 *
 * \memberof hmap
 *
 * Tham khảo: rbm_insert(struct rbmtree *t, gtype key, gtype value)
 */
struct hmap_ires hmap_insert(struct hmap *tab, gtype key, gtype value);

/**
 * Thêm cặp (key, value) vào bảng tab. Nếu key đã tồn tại thì
 * bỏ qua và trả về con trỏ tới giá trị đang có trong tab.
 *
 * @param tab Con trỏ tới bảng băm
 * @param key Khóa được thêm vào
 * @param value Giá trị giá trị được thêm vào
 * @return Trả về con trỏ tới giá trị đang được gắn với key
 * trong tab nếu đã có, hoặc trả về NULL nếu không.
 * Giá trị trả về có kiểu ::gtype*
 *
 * \memberof hmap
 *
 * Tham khảo: rbm_put(struct rbmtree *t, gtype key, gtype value)
 */
gtype *hmap_put(struct hmap *tab, gtype key, gtype value);

/**
 * Tra cứu giá trị trong bảng tab theo key.
 *
 * @param tab Con trỏ tới bảng băm.
 * @param key Khóa được sử dụng để tìm kiếm.
 * @return Trả về con trỏ tới giá trị đang được gắn với key trong tab
 * nếu tồn tại, hoặc NULL nếu ngược lại.
 *
 * \memberof hmap
 *
 * Tham khảo: rbm_value(struct rbmtree *t, gtype key)
 */
gtype *hmap_value(struct hmap *tab, gtype key);

/**
 * Nếu key không có trong tab thì bỏ qua, nếu ngược lại thì xóa cặp
 * khóa & giá trị tương ứng trong tab. Các hàm free_key và free_value được
 * gọi nếu != NULL.
 *
 * @param tab Con trỏ tới bảng băm
 * @param key Khóa cần xóa.
 * @return 1 Nếu tồn tại khóa sau khi xóa dữ liệu, 0 nếu ngược lại.
 *
 * \memberof hmap
 *
 * Tham khảo: rbm_remove(struct rbmtree *t, gtype key)
 */
int hmap_remove(struct hmap *tab, gtype key);

/**
 * Số lượng cặp khóa & giá trị đang được lưu trong hmap.
 *
 * @param tab Con trỏ tới đối tượng bảng băm.
 * @return Trả về số lượng cặp khóa/giá trị đang được lưu trong tab.
 *
 */
#define hmap_size(tab) (tab->size)

/**
 * Giải phóng bộ nhớ được cấp phát cho bảng băm tab. Các hàm free_key và
 * free_value được gọi cho từng khóa và từng giá trị nếu != NULL.
 *
 * @param tab Con trỏ tới bảng băm.
 */
#define hmap_free(tab) \
  do { \
    int _capacity = (tab)->capacity; \
    for (int _i = 0; _i < _capacity; ++_i) { \
      if (HASH_IS_REAL(tab->hashes[_i])) { \
        if ((tab)->free_key) { \
          (tab)->free_key(hmap_key_at(tab, _i)); \
        } \
        if ((tab)->free_value) { \
          (tab)->free_value(hmap_value_at(tab, _i)); \
        } \
      } \
    } \
    arr_free((tab)->keys); \
    arr_free((tab)->values); \
    arr_free((tab)->hashes); \
    free(tab); \
  } while (0)

/**
 * Làm rỗng bảng băm tab. Các hàm free_key và free_value được gọi
 * cho các cặp khóa và giá trị nếu != NULL.
 *
 * @param tab Con trỏ tới bảng băm.
 * @return Hàm không trả về giá trị.
 *
 * \memberof hmap
 */
void hmap_clear(struct hmap *tab);

/**
 * Hàm giải phóng bộ nhớ cho trường hợp con trỏ tới đối tượng bảng bắm
 * được lưu trong một cấu trúc lưu trữ khác.
 *
 * @param value Giá trị gtype đang chứa con trỏ tới bảng băm.
 * Trước tiên value.v được ép kiểu thành ::struct hmap *, sau đó con trỏ ::struct hmap *
 * được truyền cho hmap_free.
 * @return Hàm không trả về giá trị.
 *
 * \memberof gtype
 */
void gtype_free_hmap(gtype value);

gtype *hmap_next_pkey(struct hmap *, gtype*);
gtype *hmap_next_pvalue(struct hmap *, gtype*);

/**
 * Duyệt tuần tự các cặp khóa và giá trị trong map. Các tham số key và value
 * là các định danh do người sử dụng tự đặt và sẽ có kiểu ::gtype *
 *
 * @param key Định danh sẽ được sử dụng như con trỏ tới khóa.
 * @param value Định danh sẽ được sử dụng như giá trị tới khóa.
 * @param map Con trỏ tới bảng băm.
 *
 * Tham khảo: #rbm_traverse(k, v, map)
 */
#define hmap_traverse(key, value, map) \
  for(gtype *key = hmap_next_pkey(map, NULL), *value = hmap_next_pvalue(map, NULL); \
     key && value; key = hmap_next_pkey(map, key), value = hmap_next_pvalue(map, value)) \

#endif  // VEC_HMAP_H_