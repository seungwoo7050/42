/**
 * @file my_lstdelone_bonus.c
 * @brief 리스트의 특정 노드를 삭제하는 함수
 * 
 * @param lst 삭제할 노드
 * @param del 노드의 내용을 삭제할 함수
 */
#include "mylibc.h"

void my_lstdelone(t_list *lst, void (*del)(void *)) {
	if (lst && del) {
		del(lst->content);
		free(lst);
	}
}
