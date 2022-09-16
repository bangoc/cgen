#ifndef LEARNING_VEC_B01_SOLVE_H_
#define LEARNING_VEC_B01_SOLVE_H_

/**
 * đọc 1 dãy số nguyên từ 1 tệp văn bản và trả về 1 vec-tơ chứa dãy số đó.
 * Dữ liệu được cho theo định dạng: Đầu tiên là 1 số nguyên n và tiếp theo
 * là n số nguyên.
 * Lưu số nguyên vào trường l (long) của gtype.
 *
 * @param fname Tên tệp văn bản chứa dãy số cần đọc.
 * @return Con trỏ vec-tơ chứa dãy số đọc được.
 */
struct gvector *read_long(const char *fname);

/**
 * Đọc 1 dãy số thực từ 1 tệp văn bản và trả về 1 vec-tơ chứa dãy số đó.
 * Dữ liệu được cho theo định dạng: Đầu tiên là 1 số nguyên n và tiếp theo
 * là n số thực.
 * Lưu số thực vào trường d (double) của gtype.
 *
 * @param fname Tên tệp văn bản chứa dãy số cần đọc.
 * @return Con trỏ tới vec-tơ chứa dữ liệu đọc được.
 */
struct gvector *read_double(const char *fname);

/**
 * Đọc 1 tệp văn bản theo từng dòng và trả về 1 vec-tơ chứa các dòng đọc được.
 * Lưu dòng vào trường s (char *) của gtype.
 *
 * @param fname Tên tệp văn bản cần đọc
 * @return Con trỏ tới vec-tơ chứa dữ liệu đọc được
 */
struct gvector *read_lines(const char *fname);



#endif  // LEARNING_VEC_B01_SOLVE_H_