/**
 * @file my_isascii.c
 * @brief ASCII 문자 범위인지 확인하는 함수
 * 
 * @param c 확인할 문자
 * @return 1 if ASCII 범위, 0 otherwise
 */
#include "mylibc.h"

int	my_isascii(int c) {
	return (c >= 0 && c <= 127);
}
