# cgen
Triển khai khái quát các cấu trúc dữ liệu lưu trữ cơ bản

# Hướng dẫn biên dịch

Mã nguồn thư viện được đóng gói trong 2 tệp [cgen.h](all/cgen.h)
và [cgen.c](all/cgen.c) trong thư mục all.

## 1. Biên dịch trực tiếp trong môi trường dòng lệnh

Chèn [cgen.h](all/cgen.h) trong mã nguồn chương trình,

```C
#include "cgen.h"
/*...*/
```
Giả sử tệp mã nguồn chương trình là main.c, và các tệp main.c, cgen.c và cgen.h trong cùng 1 thư mục, trong điều kiện đó có thể biên dịch với gcc bằng lệnh theo định dạng:

```console
gcc -o prog main.c cgen.c --std=c11
```

## 2. Biên dịch với ninja và cmake

Cách đơn giản nhất là đặt cgen bên trong (là thư mục con của) thư mục dự án. Giả sử thư mục dự án có cấu trúc như sau:

```console
my-project
  cgen
  main.c
  CMakeLists.txt
  ...
```

Tạo tệp CMakeLists.txt với các nội dung sau:

```cmake
add_subdirectory(cgen)
include_directories(cgen)
add_executable(prog main.c)
target_link_libraries(prog bkcgen)
```

Nên thực hiện biên dịch dự án trong một thư mục độc lập, ví dụ:

```console
mkdir b
cd b
cmake .. -G Ninja
ninja

## 3. Tài liệu

Xem tài liệu chi tiết ở địa chỉ [APIs doc](https://bangoc.github.io/cgen/)
