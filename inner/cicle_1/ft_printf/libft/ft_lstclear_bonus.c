/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:59:22 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/29 03:56:08 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*cur;

	cur = *lst;
	if (lst == 0 || del == 0)
		return ;
	while (cur != 0)
	{
		tmp = (cur)->next;
		ft_lstdelone(cur, del);
		cur = tmp;
	}
	*lst = 0;
}
