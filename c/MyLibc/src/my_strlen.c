/**
 * @file ft_strlen.c
 * @brief 문자열 길이를 반환하는 함수
 * @param s 대상 문자열
 * @return size_t 문자열 길이
 */
#include "mylibc.h"

size_t my_strlen(const char *s) {
	const char *p = s;
	while (*p)
		++p;
	return (p - s);
}
