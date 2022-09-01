/*
  (C) Nguyen Ba Ngoc 2022
*/

#include "utils/builder.h"

rbm_t rbm_build(type_name_t ktyp, type_name_t vtyp) {
  gtype_cmp_t cmp;
  gtype_free_t fk;
  gtype_free_t fv;
  switch (ktyp) {
    case GTYPE_LONG:
      cmp = gtype_cmp_l;
      fk = NULL;
      break;
    case GTYPE_DOUBLE:
      cmp = gtype_cmp_d;
      fk = NULL;
      break;
    case GTYPE_CSTR:
      cmp = gtype_cmp_s;
      fk = NULL;
      break;
    case GTYPE_STR:
      cmp = gtype_cmp_s;
      fk = gtype_free_s;
      break;

    /*
      Hiếm khi được sử dụng làm khóa.
      Người dùng tự khởi tạo nếu thực sự cần thiết.
    */
    case GTYPE_PVOID:
    case GTYPE_PGTYPE:
    case GTYPE_GDL:
    case GTYPE_GSL:
    case GTYPE_GVEC:
    case GTYPE_RBM:
    case GTYPE_RBS:
    case GTYPE_HMAP:
    case GTYPE_HSET:
    case GTYPE_P1W:
    case GTYPE_P2W:
    default: return NULL;
  }

  switch (vtyp) {
    case GTYPE_LONG:
      fv = NULL;
      break;
    case GTYPE_DOUBLE:
      fv = NULL;
      break;
    case GTYPE_CSTR:
      fv = NULL;
      break;
    case GTYPE_STR:
      fv = gtype_free_s;
      break;
    case GTYPE_PVOID:
      fv = gtype_free_v;
      break;
    case GTYPE_PGTYPE:
      return NULL;
      break;
    case GTYPE_GDL:
      fv = gtype_free_gdl;
      break;
    case GTYPE_GSL:
      fv = gtype_free_gsl;
      break;
    case GTYPE_GVEC:
      fv = gtype_free_gvec;
      break;
    case GTYPE_RBM:
      fv = gtype_free_rbm;
      break;
    case GTYPE_RBS:
      fv = gtype_free_rbs;
      break;
    case GTYPE_HMAP:
      fv = gtype_free_hmap;
      break;
    case GTYPE_HSET:
      fv = gtype_free_hset;
      break;
    case GTYPE_P1W:
      fv = gtype_free_p1w;
      break;
    case GTYPE_P2W:
      fv = gtype_free_p2w;
      break;
    default: return NULL;
  }
  return rbm_create(cmp, fk, fv);
}