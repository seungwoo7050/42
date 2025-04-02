/**
 * @file my_bzero.c
 * @brief 메모리를 0으로 설정하는 함수
 * 
 * 이 함수는 주어진 메모리 영역을 n 바이트 동안 0으로 채웁니다
 * 
 * @param s 메모리 영역의 시작 주소
 * @param n 설정할 바이트 수
 */
#include "mylibc.h"

void my_bzero(void *s, size_t n) {
	unsigned char *ptr = s;
	while (n--)
		*ptr++ = 0;
}
