/**
 * @file my_isprint.c
 * @brief 출력 가능한 문자인지 확인하는 함수
 * 
 * @param c 확인할 문자
 * @return 1 if 출력 가능, 0 otherwise
 */
#include "mylibc.h"

int	my_isprint(int c) {
	return (c >= 32 && c <= 126);
}
