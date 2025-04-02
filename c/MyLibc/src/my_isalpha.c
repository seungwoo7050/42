/**
 * @file my_isalpha.c
 * @brief 알파벳 문자인지 확인하는 함수
 * 
 * @param c 확인할 문자
 * @return 1 if 알파벳 또는 숫자, 0 otherwise
 */
#include "mylibc.h"

int	my_isalpha(int c) {
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
