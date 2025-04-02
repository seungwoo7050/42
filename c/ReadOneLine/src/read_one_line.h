#ifndef READ_ONE_LINE_H
#define READ_ONE_LINE_H

#include <stddef.h>

/**
 * @brief 파일 디스크립터로부터 한 줄을 읽어 반환합니다
 * 
 * 이함수는 파일 디스크립터에서 한 중르 읽어 동적 할당된 문자열로 반환합니다
 * 반환된 문자열은 개행 문자('\n')를 포함하며, 파일 끝에 도달하거나 에러 발생 시 NULL을 반환합니다
 * 
 * 내부적으로는 단 하나의 static 변수를 사용하여 여러 파일 디스크립터를 관리합니다
 * 
 * @param fd 읽어올 파일의 파일 디스크립터
 * @return char* 읽은 한 줄의 문자열, 실패 또는 더 이상 읽을 내용이 없을 경우 NULL.
 */
char *read_one_line(int fd);

#endif  /* READ_ONE_LINE_H */