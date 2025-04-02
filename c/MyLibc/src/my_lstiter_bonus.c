/**
 * @file my_lstiter_bonus.c
 * @brief 리스트의 각 노드에 함수를 적용하는 함수
 * 
 * @param lst 리스트의 첫 번째 노드
 * @param f 적용할 함수
 */
#include "mylibc.h"

void my_lstiter(t_list *lst, void (*f)(void *)) {
	while (lst && f) {
		f(lst->content);
		lst = lst->next;
	}
}
