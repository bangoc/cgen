# cgen
Thư viện cgen bao gồm tập macro để sinh các cấu trúc lưu trữ thông dụng như vec-tơ, ánh xạ khóa-giá trị dựa trên cây đỏ-đen, và danh sách móc nối đơn.

Bên cạnh đó thư viện cũng cung cấp các triển khai khái quát của các giải thuật thông dụng dựa trên mảng như sắp xếp nhanh, tìm kiếm nhị phân, v.v..

# Ví dụ tạo ánh xạ với khóa có kiểu char * và giá trị kiểu int:
```TDECL_IMPL(simap, char *, int, si);
```
Khởi tạo đối tượng:
```struct simap *si = simap(cmps);
```
Thêm cặp khóa-giá trị:
```siput(si, "abc", 10);
```
...

Tham khảo các ví dụ trong thư mục [tests](tests).
