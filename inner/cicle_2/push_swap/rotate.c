/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:12:31 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 11:25:09 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra(t_info	**info)
{
	if (!((*info)->a_head) || !((*info)->a_head->below))
		return ;
	(*info)->a_head->above = (*info)->a_tail;
	(*info)->a_tail->below = (*info)->a_head;
	(*info)->a_tail = (*info)->a_head;
	(*info)->a_head = (*info)->a_head->below;
	(*info)->a_head->above = 0;
	(*info)->a_tail->below = 0;
	write(1, "ra\n", 3);
}

void	rb(t_info	**info)
{
	if (!((*info)->b_head) || !((*info)->b_head->below))
		return ;
	(*info)->b_head->above = (*info)->b_tail;
	(*info)->b_tail->below = (*info)->b_head;
	(*info)->b_tail = (*info)->b_head;
	(*info)->b_head = (*info)->b_head->below;
	(*info)->b_head->above = 0;
	(*info)->b_tail->below = 0;
	write(1, "rb\n", 3);
}

void	rr(t_info	**info)
{
	ra(info);
	rb(info);
	write(1, "rr\n", 3);
}
