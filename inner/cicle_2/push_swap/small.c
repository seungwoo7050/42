/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:18:28 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 19:15:25 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	small_3(t_info **info)
{
	t_stack	*cur;

	cur = (*info)->a_head;
	if (((cur->val == 2) && (cur->below->val == 1))
		|| ((cur->val == 0) && (cur->below->val == 2)))
		sa(info);
	if (cur->below->below->val == 2)
		sa (info);
	else if (cur->below->below->val == (0))
		rra (info);
	else
		ra (info);
}

void	small_4(t_info **info)
{
	int	cnt_ra;
	int	cnt_rra;

	cnt_ra = cal_abs_b((*info)->a_head, 3);
	cnt_rra = cal_abs_b((*info)->a_tail, 3);
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
	pb(info);
	small_3(info);
	pa(info);
	ra(info);
}

void	rotate_5(t_info **info, int cnt_ra, int cnt_rra)
{
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

void	small_5(t_info **info)
{
	int	cnt_ra;
	int	cnt_rra;

	cnt_ra = cal_abs_b((*info)->a_head, 4);
	cnt_rra = cal_abs_b((*info)->a_tail, 4);
	rotate_5(info, cnt_ra, cnt_rra);
	pb(info);
	cnt_ra = cal_abs_b((*info)->a_head, 3);
	cnt_rra = cal_abs_b((*info)->a_tail, 3);
	rotate_5(info, cnt_ra, cnt_rra);
	pb(info);
	small_3(info);
	pa(info);
	ra(info);
	pa(info);
	ra(info);
}
