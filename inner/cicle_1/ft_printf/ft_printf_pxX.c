/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pxX.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 06:48:36 by seungwok          #+#    #+#             */
/*   Updated: 2023/06/24 22:42:03 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_p(unsigned long long nbr, int *ps_len, int flag)
{
	if (flag == 1)
	{
		if (write(1, "0x", 2) == -1)
		{
			*ps_len = -1;
			return ;
		}
		*ps_len += 2;
	}
	if (nbr / 16 > 0)
		ft_printf_p(nbr / 16, ps_len, 2);
	if (*ps_len == -1)
		return ;
	if (write(1, &"0123456789abcdef"[nbr % 16], 1) == -1)
	{
		*ps_len = -1;
		return ;
	}
	++(*ps_len);
}

void	ft_printf_xx(unsigned int nbr, int *ps_len, char flag)
{
	if (nbr / 16 > 0)
		ft_printf_xx(nbr / 16, ps_len, flag);
	if (*ps_len == -1)
		return ;
	if (flag == 'x')
	{
		if (write(1, &"0123456789abcdef"[nbr % 16], 1) == -1)
		{
			*ps_len = -1;
			return ;
		}
	}
	else
	{
		if (write(1, &"0123456789ABCDEF"[nbr % 16], 1) == -1)
		{
			*ps_len = -1;
			return ;
		}
	}
	++(*ps_len);
}
