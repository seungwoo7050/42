/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:57:07 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 16:38:16 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	pa(t_info **info)
{
	t_stack	*tmp_a;
	t_stack	*tmp_b;

	if (!((*info)->b_head))
		return ;
	tmp_b = (*info)->b_head->below;
	tmp_a = (*info)->a_head;
	(*info)->a_head = (*info)->b_head;
	(*info)->a_head->above = 0;
	(*info)->a_head->below = tmp_a;
	if (!tmp_a)
		(*info)->a_tail = (*info)->a_head;
	else
		(*info)->a_head->below->above = (*info)->a_head;
	(*info)->b_head = tmp_b;
	if (!((*info)->b_head))
		(*info)->b_tail = (*info)->b_head;
	else
		(*info)->b_head->above = 0;
	write(1, "pa\n", 3);
}

void	pb(t_info **info)
{
	t_stack	*tmp_a;
	t_stack	*tmp_b;

	if (!((*info)->a_head))
		return ;
	tmp_a = (*info)->a_head->below;
	tmp_b = (*info)->b_head;
	(*info)->b_head = (*info)->a_head;
	(*info)->b_head->above = 0;
	(*info)->b_head->below = tmp_b;
	if (!tmp_b)
		(*info)->b_tail = (*info)->b_head;
	else
		(*info)->b_head->below->above = (*info)->b_head;
	(*info)->a_head = tmp_a;
	if (!((*info)->a_head))
		(*info)->a_tail = (*info)->a_head;
	else
		(*info)->a_head->above = 0;
	write(1, "pb\n", 3);
}
