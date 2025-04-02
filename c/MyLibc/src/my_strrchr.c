/**
 * @file my_strrchr.c
 * @brief 문자열에서 특정 문자의 마지막 위치를 찾는 함수
 * 
 * @param s 검색할 문자열
 * @param c 찾을 문자
 * @return char* 마지막으로 발견된 위치의 포인터, 없으면 NULL
 */
#include "mylibc.h"

char *my_strrchr(const char *s, int c) {
	const char *last = NULL;
	while (*s) {
		if (*s == (char)c)
			last = s;
		++s;
	}
	return (c == 0) ? (char *)s : (char *)last;
}
