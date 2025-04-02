/**
 * @file my_strlcpy.c
 * @brief 문자열을 안전하게 복사하는 함수
 * 
 * @param dst 대상 버퍼
 * @param src 원본 문자열
 * @param size 대상버퍼의 크기
 * @return size_t 원본 문자열의 길이
 */
#include "mylibc.h"

size_t my_strlcpy(char *dst, const char *src, size_t size) {
	size_t	srclen = my_strlen(src);
	if (size == 0)
		return srclen;
	size_t i;
	for (i = 0; i < size - 1 && src[i]; i ++)
		dst[i] = src[i];
	dst[i] = '\0';
	return srclen;
}
