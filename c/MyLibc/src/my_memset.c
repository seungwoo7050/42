/**
 * @file my_memset.c
 * @brief 메모리 블록을 특정 값으로 설정하는 함수
 * 
 * @param b 설정할 메모리 블록
 * @param c 설정할 값 (정수)
 * @param len 설정할 바이트 수
 * @return void* 설정된 메모리 블록의 포인터
 */
#include "mylibc.h"

void *my_memset(void *b, int c, size_t len) {
	unsigned char	*ptr = b;
	while (len--)
		*ptr++ = (unsigned char)c;
	return b;
}
