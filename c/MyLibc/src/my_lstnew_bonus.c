/**
 * @file ft_lstnew_bonus.c
 * @brief 
 * 
 * @param content 
 * @return t_list* 
 */
#include "mylibc.h"

t_list *my_lstnew(void *content) {
	t_list	*node = malloc(sizeof(t_list));
	if (!node)
		return NULL;
	node->content = content;
	node->next = NULL;
	return node;
}
