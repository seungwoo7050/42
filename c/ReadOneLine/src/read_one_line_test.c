#include "read_one_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief 테스트 프로그램: 주어진 파일의 내용을 한 줄씩 읽어 출력합니다
 * 
 * @param argc 인자 개수
 * @param argv 파일 경로를 포함한 인자 배열
 * @return int 종료 코드
 */
int main(int argc, char **argv) {
    int fd;
    char* line;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("파일 열기 실패");
        return EXIT_FAILURE;
    }

    while ((line = read_one_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd);
    return EXIT_SUCCESS;
}