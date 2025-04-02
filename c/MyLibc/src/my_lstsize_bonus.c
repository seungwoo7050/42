/**
 * @file my_lstsize_bonus.c
 * @brief 리스트의 노드 개수를 계산하는 함수
 * 
 * @param lst 리스트의 첫 번째 노드
 * @return int 노드의 개수
 */
#include "mylibc.h"

int	my_lstsize(t_list *lst) {
	int count = 0;
	while (lst) {
		++count;
		lst = lst->next;
	}
	return count;
}
