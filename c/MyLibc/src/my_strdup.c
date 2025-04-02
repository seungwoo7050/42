/**
 * @file my_strdup.c
 * @brief 문자열을 복제하는 함수
 * 
 * @param s 복제할 문자열
 * @return char* 복제된 문자열의 포인터, 할당 실패 시 NULL 반환
 */
#include "mylibc.h"

char *my_strdup(const char *s) {
	size_t len = my_strlen(s);
	char *dup = malloc(len + 1);
	if (!dup)
		return NULL;
	for (size_t i = 0; i <= len; i++)
		dup[i] = s[i];
	return dup;
}
