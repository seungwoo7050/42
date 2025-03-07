/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:41:59 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 20:06:25 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	cal_chunk(t_info **info)
{
	int	chunk;

	chunk = 14;
	if (((*info)->size) < 100)
		return (chunk);
	else
		return (chunk + (((*info)->size) / 100 * 3));
}

int	cal_abs_a(t_stack *cur, int val)
{
	int	abs;

	abs = 0;
	if (!(cur->above))
	{
		while (cur)
		{
			if (cur->val <= val)
				return (abs);
			cur = cur->below;
			abs++;
		}
	}
	else
	{
		while (cur)
		{
			if (cur->val <= val)
				return (abs + 1);
			cur = cur->above;
			abs++;
		}
	}
	exit (1);
}

int	cal_abs_b(t_stack *cur, int val)
{
	int	abs;

	abs = 0;
	if (!(cur->above))
	{
		while (cur)
		{
			if (cur->val == val)
				return (abs);
			cur = cur->below;
			abs++;
		}
	}
	else
	{
		while (cur)
		{
			if (cur->val == val)
				return (abs + 1);
			cur = cur->above;
			abs++;
		}
	}
	exit (1);
}
