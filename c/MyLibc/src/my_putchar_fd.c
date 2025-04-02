/**
 * @file my_putchar_fd.c
 * @brief 파일 디스크립터에 문자를 출력하는 함수
 * 
 * @param c 출력할 문자
 * @param fd 출력한 파일 디스크립터
 */
#include "mylibc.h"

void my_putchar_fd(char c, int fd) {
	if (fd >= 0)
		write (fd, &c, 1);
}
