# cgen
Thư viện cgen hiện đang bao gồm tập macro để sinh các cấu trúc lưu trữ thông dụng như vec-tơ, ánh xạ khóa-giá trị dựa trên cây đỏ-đen, và danh sách móc nối đơn.

Bên cạnh đó thư viện cũng cung cấp các triển khai khái quát của các giải thuật thông dụng dựa trên mảng như sắp xếp nhanh, tìm kiếm nhị phân, v.v..

Trong tương lai gần nhất dự kiến sẽ bổ xung thêm bảng băm, và xa hơn có thể là những thành phần hữu ích khác nữa.

Tất cả mã nguồn cần thiết đã được đóng gói trong 1 tệp tiêu đề [cgen.h](all/cgen.h) trong thư mục [all](all).
Để sử dụng chỉ cần chèn vào đơn vị biên dịch, ví dụ đơn giản nhất:
```C
#include "cgen.h"
```

## Ví dụ tạo ánh xạ char * => int:
```C
TDECL_IMPL(simap, char *, int, si);
```
Khởi tạo đối tượng:
```C
struct simap *si = simap(cmps);
```
Thêm cặp khóa-giá trị:
```C
siput(si, "abc", 10);
```
...

Tham khảo các ví dụ trong thư mục [tests/cgen](tests/cgen).
