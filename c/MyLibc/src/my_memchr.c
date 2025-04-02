/**
 * @file ft_memchr.c
 * @brief 메모리 블록에서 특정 문자를 찾는 함수
 * 
 * @param b 검색할 메모리 블록
 * @param c 찾을 문자
 * @param n 검색할 바이트 수
 * @return void* 
 */
#include "mylibc.h"

void	*my_memchr(const void *b, int c, size_t n) {
	const unsigned char *p = b;
	while (n--) {
		if (*p == (unsigned char)c)
			return (void *)p;
		++p;
	}
	return NULL;
}