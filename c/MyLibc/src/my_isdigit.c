/**
 * @file my_isdigit.c
 * @brief 숫자인지 확인하는 함수
 * 
 * @param c 확인할 문자
 * @return 1 if 숫자, 0 otherwise
 */
#include "mylibc.h"

int	my_isdigit(int c) {
	return (c >= '0' && c <= '9');
}
