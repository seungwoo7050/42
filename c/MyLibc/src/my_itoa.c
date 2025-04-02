/**
 * @file my_itoa.c
 * @brief 정수를 문자열로 변환하는 함수
 * 
 * @param n 변환할 정수
 * @return char* 변환된 문자열의 포인터, 할당 실패 시 NULL 반환
 */
#include "mylibc.h"
static int count_digit(int n) {
	int count = (n <= 0) ? 1 : 0;
	while (n) {
		n /= 10;
		++count;
	}
	return count;
}

char *my_itoa(int n) {
	int sign = (n < 0) ? -1 : 1;
	int digits = count_digit(n);
	char *str = malloc(digits + 1);
	if (!str)
		return NULL;
	str[digits] = '\0';
	long num = n;
	if (num < 0)
		num = -num;
	while (digits--) {
		str[digits] = (num % 10) + '0';
		num /= 10;
		if (digits == 0 && sign == -1)
			str[0] = '-';
	}
	return str;
}