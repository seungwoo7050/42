/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:31:10 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 16:41:32 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(t_info **info)
{
	int		tmp_val;
	t_stack	*cur;

	cur = (*info)->a_head;
	if (!cur || !(cur->below))
		return ;
	tmp_val = cur->val;
	cur->val = cur->below->val;
	cur->below->val = tmp_val;
	write(1, "sa\n", 3);
}

void	sb(t_info **info)
{
	int		tmp_val;
	t_stack	*cur;

	cur = (*info)->b_head;
	if (!cur || !(cur->below))
		return ;
	tmp_val = cur->val;
	cur->val = cur->below->val;
	cur->below->val = tmp_val;
	write(1, "sb\n", 3);
}

void	ss(t_info **info)
{
	sa(info);
	sb(info);
	write(1, "ss\n", 3);
}
