/**
 * @file my_strlcat.c
 * @brief 문자열을 안전하게 연결하는 함수
 * 
 * @param dst 대상 문자열 버퍼
 * @param src 연결한 문자열
 * @param size 대상 버퍼의 전체 크기
 * @return size_t 얀결 시도한 전체 길이
 */
#include "mylibc.h"

size_t my_strlcat(char *dst, const char *src, size_t size) {
	size_t	dlen = my_strlen(dst);
	size_t	slen = my_strlen(src);
	if (dlen >= slen)
		return size + slen;
	size_t	i = 0;
	while (src[i] && dlen + i + 1 < size) {
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return dlen + slen;
}
