#include "read_one_line_utils.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief 두 문자열 s1과 s2를 연결하여 새 문자열을 반환합니다
 * 
 * @param s1 첫 번째 문자열
 * @param s2 두 번째 문자열
 * @return char* 합쳐진 새 문자열, 메모리 할당 실패 시 NULL
 */
char *strjoin(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *join = (char *)malloc(len1 + len2 + 1);
    if (!join)
        return NULL;
    memcpy(join, s1, len1);
    memcpy(join + len1, s2, len2);
    join[len1 + len2] = '\0';
    return join;
}

/**
 * @brief 입력 문자열 s의 일부를 잘라내어 새 문자열을 생성합니다
 * 
 * @param s 입력 문자열
 * @param start 복사를 시작할 인덱스
 * @param len 복사할 최대 길이
 * @return char* 잘라낸 새 문자열, 메모리 할당 실패 시 NULL
 */
char *substr(const char *s, unsigned int start, size_t len) {
    size_t slen = strlen(s);
    char* sub;

    if (start >= slen)
        return strdup("");
    if (len > slen - start)
        len = slen - start;
    sub = (char *)malloc(len + 1);
    if (!sub)
        return NULL;
    memcpy(sub, s + start, len);
    sub[len] ='\0';
    return sub;
}