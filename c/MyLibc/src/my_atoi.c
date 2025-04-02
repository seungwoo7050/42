/**
 * @file my_atoi.c
 * @brief 문자열을 정수로 변환하는 함수
 * 
 * 이 함수는 문자열을 정수로 변환하여 반환합니다
 * 
 * @param s		변환할 문자열
 * @return int	변환된 정수 값
 */
#include "mylibc.h"

int	my_atoi(const char *str) {
	int sign = 1;
	long result = 0;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		++str;
	if (*str == '+' || *str == '-') {
		if (*str == '-')
			sign = -1;
		++str;
	}
	while (*str >= '0' && *str <= '9') {
		result = result * 10 + (*str - '0');
		++str;
	}
	return sign * (int)result;
}