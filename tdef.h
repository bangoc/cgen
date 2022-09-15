#ifndef TDEF_H_
#define TDEF_H_

/** @file
 * @brief Quy tắc sử dụng kiểu con trỏ ở dạng đủ thông tin, không tạo
 * tên tương đương cho kiểu con trỏ (typedef) được áp dụng trong
 * phạm vi thư viện này.
 *
 * Tuy nhiên để tiếp tục hỗ trợ các mã nguồn đã sử dụng các tên tương
 * đương (rút gọn) như gvec_t, các typedef sẽ được tập hợp ở đây.
 * Các lựa chọn là riêng tư, người dùng cũng có thể tự quy ước các tên
 * rút gọn với typedef bên ngoài phạm vi thư viện nếu muốn.
 *
 * Sử dụng kiểu con trỏ ở dạng đầy đủ sẽ dễ đọc hơn, ví dụ
 * khi sử dụng kèm const, phép gán và các toán tử khác, v.v..
 * Người dùng nên chuyển sang dạng đầy đủ thay cho các tên tương đương
 * và không nên quy ước các tên rút gọn cho kiểu con trỏ.
 */

typedef struct gvector *gvec_t;
typedef struct dlnode *dln_t;
typedef struct dllist *dll_t;
typedef struct idlnode *idn_t;
typedef struct slnode *sln_t;
typedef struct sllist *sll_t;
typedef struct islnode *isn_t;
typedef struct gdlnode *gdn_t;
typedef struct gdllist *gdl_t;
typedef struct gslnode *gsn_t;
typedef struct gsllist *gsl_t;
typedef struct si2ways *si2w_t;
typedef struct bnnode *bnn_t;
typedef struct bntree *bnt_t;
typedef struct rbnode *rbn_t;
typedef struct gbsnode *gbn_t;
typedef struct gbstree *gbt_t;
typedef struct grbnode *grn_t;
typedef struct grbtree *grt_t;
typedef struct rbmnode *rbmn_t;
typedef struct rbmtree *rbm_t;
typedef struct rbstree *rbs_t;
typedef struct hmap *hmap_t;
typedef struct hset *hset_t;
typedef struct p1way *p1w_t;
typedef struct p2ways *p2w_t;

#endif  // TDEF_H_