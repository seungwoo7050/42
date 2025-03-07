/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:04:49 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 18:36:07 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi(const char *s)
{
	long long	num;
	int			sign;

	num = 0;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		++s;
	}
	if (*s == '0' && *(s + 1) != 0)
		print_error ();
	while (*s >= '0' && *s <= '9')
	{
		num = num * 10 + (*s - '0');
		++s;
	}
	if (*s)
		print_error ();
	num *= sign;
	if (num > 2147483647 || num < -2147483648)
		print_error ();
	return ((int)num);
}
