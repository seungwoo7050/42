/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 06:55:24 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/29 03:28:19 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*nextlst;

	if (lst == 0 || new == 0)
		return ;
	if (lst != 0 && *lst == 0)
	{
		*lst = new;
		return ;
	}
	nextlst = *lst;
	while (nextlst->next != 0)
		nextlst = nextlst->next;
	nextlst->next = new;
}
