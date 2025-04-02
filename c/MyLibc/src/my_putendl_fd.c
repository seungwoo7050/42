/**
 * @file ft_putendl_fd.c
 * @brief 파일 디스크립터에 문자열과 개행 문자를 출력하는 함수
 * 
 * @param s 출력할 문자열
 * @param fd 출력한 파일 디스크립터
 */
#include "mylibc.h"

void my_putendl_fd(char *s, int fd) {
	if (s && fd >= 0) {
		my_putstr_fd(s, fd);
		write(fd, "\n", 1);
	}
}	
