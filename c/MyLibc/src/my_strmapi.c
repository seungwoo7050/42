/**
 * @file my_strmapi.c
 * @brief 문자열의 각 문자를 인덱스를 기반으로 함수를 적용하여 새로운 문자열을 생성하는 함수
 * 
 * @param s 원본 문자열
 * @param f 각 문자를 변환할 함수 (인덱스와 문자를 인자로 받음)
 * @return char* 변환된 문자열의 포인터, 할당 실패 시 NULL 반환
 */
#include "mylibc.h"

char *my_strmapi(char const *s, char (*f)(unsigned int, char)) {
	if (!s || !f)
		return NULL;
	
	size_t len = my_strlen(s);
	char *res = malloc(len + 1);
	if (!res)
		return NULL;
	for (unsigned int i = 0; i < len; i++)
		res[i] = f(i, s[i]);
	res[len] = '\0';
	return res;
}
