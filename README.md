# cgen
Triển khai khái quát các cấu trúc dữ liệu lưu trữ cơ bản

### Sử dụng bảng tham chiếu s2i (char*->int)

```C
  bn_tree_t t = s2i_create();
  s2i_insert(t, "Mot", 1);
  s2i_insert(t, "Hai", 2);
  s2i_insert(t, "Ba", 3);
  s2i_value(t, "Hai");
  s2i_delete(t, "Ba");
  s2i_free(t);
```
