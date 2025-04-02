/**
 * @file my_memcmp.c
 * @brief 두 메모리 블록을 비교하는 함수.
 * 
 * @param b1 첫 번째 메모리 블록
 * @param b2 두 번째 메모리 블록
 * @param n 비교할 바이트 수
 * @return int 첫 번째 다른 바이트의 차이, 같으면 0
 */
#include "mylibc.h"

int	my_memcmp(const void *b1, const void *b2, size_t n) {
	const unsigned char	*p1 = b1;
	const unsigned char	*p2 = b2;
	while (n--) {
		if (*p1 != *p2)
			return *p1 - *p2;
		++p1;
		++p2;
	}
	return 0;
}
