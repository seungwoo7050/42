/**
 * @file my_striteri.c
 * @brief 문자열의 각 문자를 포인터를 기반으로 함수를 적용하여 새로운 문자열을 생성하는 함수
 * 
 * @param s 대상 문자열
 * @param f 각 문자를 처리할 함수 (인덱스와 문자의 주소를 인자로 받음)
 * @return char* 변환된 문자열의 포인터, 할당 실패 시 NULL 반환
 */
#include "mylibc.h"

void my_striteri(char *s, void (*f)(unsigned int, char *)) {
	if (!s || !f)
		return;
	for (unsigned int i = 0; s[i]; i++)
		f(i, &s[i]);
}
