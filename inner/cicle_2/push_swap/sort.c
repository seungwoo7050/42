/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 22:25:39 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 20:17:35 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	search_val_a(t_info **info, int val)
{
	int	cnt_ra;
	int	cnt_rra;

	cnt_ra = cal_abs_a((*info)->a_head, val);
	cnt_rra = cal_abs_a((*info)->a_tail, val);
	if (cnt_ra <= cnt_rra)
	{
		while (cnt_ra > 0)
		{
			ra(info);
			cnt_ra--;
		}
	}
	else
	{
		while (cnt_rra > 0)
		{
			rra(info);
			cnt_rra--;
		}
	}
}

void	a_to_b(t_info **info, int chunk, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		search_val_a(info, i + chunk);
		if ((*info)->a_head->val <= i)
		{
			pb(info);
			i++;
		}
		else if (((*info)->a_head->val > i)
			&& ((*info)->a_head->val <= (i + chunk)))
		{
			pb(info);
			rb(info);
			i++;
		}		
	}
}

void	b_to_a(t_info **info, int val)
{
	int	cnt_rb;
	int	cnt_rrb;

	if (val == -1)
		return ;
	cnt_rb = cal_abs_b((*info)->b_head, val);
	cnt_rrb = cal_abs_b((*info)->b_tail, val);
	if (cnt_rb <= cnt_rrb)
	{
		while (cnt_rb > 0)
		{
			rb(info);
			cnt_rb--;
		}
	}
	else
	{
		while (cnt_rrb > 0)
		{
			rrb(info);
			cnt_rrb--;
		}
	}
	pa(info);
	b_to_a(info, val - 1);
}

void	sort_start(t_info **info)
{
	int	chunk;

	chunk = cal_chunk(info);
	if ((*info)->size == 2)
		sa(info);
	else if ((*info)->size == 3)
		small_3(info);
	else if ((*info)->size == 4)
		small_4(info);
	else if ((*info)->size == 5)
		small_5(info);
	else
	{
		a_to_b(info, chunk, (*info)->size);
		b_to_a(info, (((*info)->size) - 1));
	}
}
