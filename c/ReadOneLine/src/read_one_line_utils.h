#ifndef READ_ONE_LINE_UTILS_H
#define READ_ONE_LINE_UTILS_H

#include <stddef.h>

/**
 * @brief 두 문자열을 합쳐 새로운 문자열을 생성합니다
 * 
 * 이 함수는 s1과 s2를 연결하여 새 문자열을 반환합니다
 * 
 * @param s1 첫 번째 문자열
 * @param s2 두 번째 문자열
 * @return char* 합쳐진 새 문자열, 메모리 할당 실패 시 NULL
 */
char *strjoin(const char *s1, const char *s2);

/**
 * @brief 입력 문자열 s의 일부를 잘라내어 새 문자열을 생성합니다
 * 
 * @param s 입력 문자열
 * @param start 복사를 시작할 인덱스
 * @param len 복사할 최대 길이
 * @return char* 잘라낸 새 문자열, 메모리 할당 실패 시 NULL
 */
char* substr(const char *s, unsigned int start, size_t len);

#endif  /* READ_ONE_LINE_UTILS_H */