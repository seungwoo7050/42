/**
 * @file my_memmove.c
 * @brief 메모리 영역을 안전하게 복사하는 함수
 * 
 * @param dst 복사할 대상
 * @param src 복사할 원본
 * @param n 복사할 바이트 수
 * @return void* 복사된 대상의 포인터
 */
#include "mylibc.h"

void *my_memmove(void *dst, const void *src, size_t len) {

	unsigned char	*d = dst;
	const unsigned char	*s = src;
	if (d < s) {
		while (len--)
			*d++ = *s++;
	} else {
		d += len;
		s += len;
		while (len--)
			*--d = *--s;
	}
	return dst;
}
