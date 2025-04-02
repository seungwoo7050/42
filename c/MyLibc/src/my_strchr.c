/**
 * @file my_strchr.c
 * @brief 문자열에서 특정 문자를 찾는 함수
 * 
 * @param s 검색할 문자열
 * @param c 찾을 문자
 * @return char* 찾은 위치의 포인터, 없으면 NULL
 */
#include "mylibc.h"

char *my_strchr(const char *s, int c) {
	while (*s) {
		if (*s == (char)c)
			return (char *)s;
		++s;
	}
	return (c == 0) ? (char *)s : NULL;
}
