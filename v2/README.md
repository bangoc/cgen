# cgen
Triển khai khái quát các cấu trúc dữ liệu lưu trữ cơ bản

# Hướng dẫn biên dịch

Tệp mã nguồn, ví dụ main.c:

```C
#include "cgen.h"
/*...*/
```

Trong đó all.h là tệp tổng hợp các tệp tiêu đề của cgen.

## 1. Biên dịch với gcc trong môi trường dòng lệnh

```console
gcc -o prog main.c ${CGEN_PATH}/all.c -I ${CGEN_PATH}
```

Trong đó ${CGEN_PATH} là đường dẫn tới thư mục cgen;

all.c là tệp tổng hợp các tệp .c (mã nguồn) của cgen.

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
```
## 3. Sử dụng định dạng 1 tệp
```C
#include "cgen.h"
/*...*/
```
gcc -o prog main.c cgen.c

Các tệp tổng hợp cgen.h và cgen.c có thể được tải về từ trang [Xuất bản (release)](https://github.com/bangoc/cgen/releases), hoặc tự tạo với công cụ merge trong mega-unit.

## 4. Tài liệu

Xem tài liệu chi tiết ở địa chỉ [APIs doc](https://bangoc.github.io/cgen/)
