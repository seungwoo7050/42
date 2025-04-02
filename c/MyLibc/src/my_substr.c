/**
 * @file my_substr.c
 * @brief 문자열의 일부를 추출하는 함수.
 * 
 * @param s 원본 문자열
 * @param start 추출 시작 인덱스
 * @param len 추출할 최대 길이
 * @return char* 추출된 부분 문자열의 포인터, 할당 실패 시 NULL 반환
 */
#include "mylibc.h"

char *my_substr(char const *s, unsigned int start, size_t len) {
	size_t slen = my_strlen(s);
	if (start >= slen)
		my_strdup("");
	if (len > slen - start)
		len = slen - start;
	char *sub = malloc(len + 1);
	if (!sub)
		return NULL;
	for (size_t i = 0; i < len; i++)
		sub[i] = s[start + i];
	sub[len] = '\0';
	return sub;
}
