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
typedef struct dln *dln_t;
typedef struct dll *dll_t;
typedef struct idn *idn_t;
typedef struct sln *sln_t;
typedef struct sll *sll_t;
typedef struct isn *isn_t;
typedef struct gdn *gdn_t;
typedef struct gdl *gdl_t;
typedef struct gsn *gsn_t;
typedef struct gsl *gsl_t;
typedef struct s2w *s2w_t;
typedef struct bnn *bn_node_t;
typedef struct bnt *bn_tree_t;
typedef struct rbn *rb_node_t;
typedef struct gbsn *gbs_node_t;
typedef struct gbst *gbs_tree_t;
typedef struct grbn *grb_node_t;
typedef struct grbt *grb_tree_t;
typedef struct rbmn *rbm_node_t;
typedef struct rbmt *rbm_t;
typedef struct rbst *rbs_t;
typedef struct hmap *hmap_t;
typedef struct hset *hset_t;
typedef struct p1way *p1w_t;
typedef struct p2ways *p2w_t;

#endif  // TDEF_H_