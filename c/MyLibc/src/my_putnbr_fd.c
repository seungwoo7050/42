/**
 * @file ft_putnbr_fd.c
 * @brief 파일 디스크립터에 정수를 출력하는 함수
 * 
 * @param n 출력할 정수
 * @param fd 출력한 파일 디스크립터
 */
#include "mylibc.h"

void	my_putnbr_fd(int n, int fd) {
	long num = n;
	if (num < 0 ) {
		my_putchar_fd('-', fd);
		num = -num;
	}
	if (num >= 10)
		my_putnbr_fd(num / 10, fd);
	my_putchar_fd((num % 10) + '0', fd);
}
