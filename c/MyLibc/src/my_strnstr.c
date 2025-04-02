/**
 * @file my_strnstr.c
 * @brief 문자열 내에서 부분 문자열을 찾는 함수
 * 
 * @param haystack 검색 대상 문자열
 * @param needle 찾을 부분 문자열
 * @param len 검색할 최대 바이트 수
 * @return char* 찾은 위치의 포인터, 없으면 NULL
 */
#include "mylibc.h"

char *my_strnstr(const char *haystack, const char *needle, size_t len) {
	size_t nlen = my_strlen(needle);
	if (nlen == 0)
		return (char *)haystack;
	for (size_t i = 0; haystack[i] && i <= len - nlen; i++) {
		if (my_strncmp(&haystack[i], needle, nlen) == 0)
			return (char *)&haystack[i];
	}
	return NULL;
}
