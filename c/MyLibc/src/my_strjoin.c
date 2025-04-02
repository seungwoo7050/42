/**
 * @file my_strjoin.c
 * @brief 두 문자열을 연결하여 새로운 문자열을 반환하는 함수
 * 
 * @param s1 연결할 앞 문자열
 * @param s2 연결할 뒷 문자열
 * @return char* 연결된 문자열의 포인터, 할당 실패 시 NULL 반환
 */
#include "mylibc.h"

char *my_strjoin(char const *s1, char const *s2) {
	size_t		len1 = my_strlen(s1);
	size_t		len2 = my_strlen(s2);
	char* joined = malloc(len1 + len2 + 1);
	if (!joined)
		return NULL;
	for (size_t i = 0; i < len1; i++)
		joined[i] = s1[i];
	for (size_t i = 0; i < len2; i++)
		joined[len1 + i] = s2[i];
	joined[len1 + len2] = '\0';
	return joined;
}