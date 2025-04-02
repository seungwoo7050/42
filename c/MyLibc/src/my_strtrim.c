/**
 * @file my_strtrim.c
 * @brief 문자열의 시작과 끝에서 지정된 문자들을 제거하는 함수
 * 
 * @param s 원본 문자열
 * @param set 제거할 문자 집합
 * @return char* 트림된 문자열의 포인터, 할당 실패 시 NULL 반환
 */
#include "mylibc.h"

char *my_strtrim(char const *s, char const *set) {
	size_t start = 0, end = my_strlen(s);
	while (s[start] && my_strchr(set, s[start]))
		++start;
	while (end > start && my_strchr(set, s[end - 1]))
		--end;
	return my_substr(s, start, end - start);
}