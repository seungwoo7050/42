/**
 * @file ft_lstmap_bonus.c
 * @brief 리스트의 각 노드에 함수를 적용하여 새로운 리스트를 생성하는 함수
 * 
 * @param lst 원본 리스트의 첫 번째 노드
 * @param f 각 노드의 내용을 변환할 함수
 * @param del 변환 실패 시 노드를 삭제할 함수
 * @return t_list* 새로 생성된 리스트의 첫 번째 노드, 할당 실패 시 NULL
 */
#include "mylibc.h"

t_list *my_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *)) {
	if (!lst || !f || !del )
		return NULL;
	t_list *new_list = NULL;
	t_list *new_elem;
	while (lst) {
		new_elem = my_lstnew(f(lst->content));
		if (!new_elem) {
			my_lstclear(&new_list, del);
			return NULL;
		}
		my_lstadd_back(&new_list, new_elem);
		lst = lst->next;
	}
	return new_list;
}