/**
 * @file my_toupper.c
 * @brief 대문자를 소문자로 변환하는 함수
 * 
 * @param c 변환할 문자
 * @return int 변환된 문자
 */
#include "mylibc.h"

int	my_toupper(int c) {
	return (c >= 'a' && c <= 'z') ? c - 32 : c;
}
