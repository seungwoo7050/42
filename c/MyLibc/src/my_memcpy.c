/**
 * @file my_memcpy.c
 * @brief 메모리 블록을 복사하는 함수
 * 
 * @param dst 복사할 대상
 * @param src 복사할 원본
 * @param n 복사할 바이트 수
 * @return void* 복사된 대상의 포인터, src와 dst가 NULL이면 NULL
 */
#include "mylibc.h"

void *my_memcpy(void *dst, const void *src, size_t n) {
	if (!dst && !src)
		return NULL;
	unsigned char *d = dst;
	const unsigned char *s = src;
	while (n--)
		*d++ = *s++;
	return dst;
}
