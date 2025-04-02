/**
 * @file my_lstclear_bonus.c
 * @brief 리스트 전체를 삭제하는 함수
 * 
 * @param alst 리스트의 포인터에 대한 포인터
 * @param del 노드의 내용을 삭제할 함수
 */
#include "mylibc.h"

void my_lstclear(t_list **alst, void (*del)(void *)) {
	if (!alst || !del)
		return;
	t_list *temp;
	while (*alst) {
		temp = (*alst)->next;
		my_lstdelone(*alst, del);
		*alst = temp;
	}
}
