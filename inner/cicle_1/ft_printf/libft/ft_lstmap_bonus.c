/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:14:21 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/29 03:55:58 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;
	void	*p;

	if (lst == 0 || f == 0 || del == 0)
		return (0);
	res = 0;
	while (lst != 0)
	{
		p = f(lst->content);
		new = ft_lstnew(p);
		if (new == 0)
		{
			del(p);
			del(new);
			ft_lstclear(&res, del);
			return (0);
		}
		ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	new->next = 0;
	return (res);
}
