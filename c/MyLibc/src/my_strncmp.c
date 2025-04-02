/**
 * @file my_strncmp.c
 * @brief 두 문자열을 n 바이트까지 비교하는 함수
 * 
 * @param s1 첫 번째 문자열
 * @param s2 두 번째 문자열
 * @param n 비교할 최대 바이트 수
 * @return int 차이 값, 같으면 0
 */
#include "mylibc.h"

int	my_strncmp(const char *s1, const char *s2, size_t n) {
	size_t	i = 0;
	while (i < n && s1[i] && s1[i] == s2[i])
		++i;
	return i == n ? 0 : (unsigned char)s1[i] - (unsigned char)s2[i];
}
