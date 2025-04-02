/**
 * @file my_lstlast_bonus.c
 * @brief 리스트의 마지막 노드를 반환하는 함수
 * 
 * @param lst 리스트의 첫 번째 노드
 * @return t_list* 마지막 노드의 포인터, 리스트가 비어있으면 NULL
 */
#include "mylibc.h"

t_list *my_lstlast(t_list *lst) {
	if (!lst)
		return NULL;
	while (lst->next)
		lst = lst->next;
	return lst;
}
