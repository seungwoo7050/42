/**
 * @file my_isalnum.c
 * @brief 알파벳 또는 숫자인지 확인하는 함수
 * 
 * @param c 확인할 문자
 * @return 1 if 알파벳 또는 숫자, 0 otherwise
 */
#include "mylibc.h"

int	my_isalnum(int c) {
	return (my_isalpha(c) || my_isdigit(c));
}
