/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:18:08 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 16:25:49 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(t_info	**info)
{
	if (!((*info)->a_head) || !((*info)->a_head->below))
		return ;
	(*info)->a_head->above = (*info)->a_tail;
	(*info)->a_tail->below = (*info)->a_head;
	(*info)->a_head = (*info)->a_tail;
	(*info)->a_tail = (*info)->a_tail->above;
	(*info)->a_head->above = 0;
	(*info)->a_tail->below = 0;
	write(1, "rra\n", 4);
}

void	rrb(t_info	**info)
{
	if (!((*info)->b_head) || !((*info)->b_head->below))
		return ;
	(*info)->b_head->above = (*info)->b_tail;
	(*info)->b_tail->below = (*info)->b_head;
	(*info)->b_head = (*info)->b_tail;
	(*info)->b_tail = (*info)->b_tail->above;
	(*info)->b_head->above = 0;
	(*info)->b_tail->below = 0;
	write(1, "rrb\n", 4);
}

void	rrr(t_info	**info)
{
	rra(info);
	rrb(info);
	write(1, "rrr\n", 4);
}
