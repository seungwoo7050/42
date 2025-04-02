/**
 * @file my_calloc.c
 * @brief 메모리 할당 및 초기화 함수
 * 
 * 이 함수는 num * size 바이트의 메모리를 할당하고 0으로 초기화합니다.
 * 
 * @param count 할당할 요소의 수
 * @param size 각 요소의 크기
 * @return void* 할당된 메모리의 포인터, 실패 시 NULL 반환
 */
#include "mylibc.h"

void	*my_calloc(size_t count, size_t size) {
	void *ptr = malloc(count * size);
	if (!ptr)
		return NULL;
	my_bzero(ptr, count * size);
	return ptr;
}