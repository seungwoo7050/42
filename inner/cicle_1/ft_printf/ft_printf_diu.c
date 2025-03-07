/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_diu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 06:48:29 by seungwok          #+#    #+#             */
/*   Updated: 2023/06/24 23:11:05 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_di_negativehandling(int nbr, int *ps_len)
{
	if (nbr == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
		{
			*ps_len = -1;
			return ;
		}
		*ps_len += 11;
		return ;
	}
	if (nbr < 0)
	{
		if (write(1, "-", 1) == -1)
		{
			*ps_len = -1;
			return ;
		}
		++(*ps_len);
		return ;
	}
}

void	ft_printf_di(int nbr, int *ps_len)
{
	if (nbr == -2147483648)
	{
		ft_printf_di_negativehandling(nbr, ps_len);
		return ;
	}	
	if (nbr < 0)
	{
		ft_printf_di_negativehandling(nbr, ps_len);
		nbr *= -1;
	}
	if (nbr / 10 > 0)
		ft_printf_di(nbr / 10, ps_len);
	if (*ps_len == -1)
		return ;
	if (write(1, &"0123456789"[nbr % 10], 1) == -1)
	{
		*ps_len = -1;
		return ;
	}
	++(*ps_len);
}

void	ft_printf_u(unsigned int nbr, int *ps_len)
{
	if (nbr / 10 > 0)
		ft_printf_u(nbr / 10, ps_len);
	if (*ps_len == -1)
		return ;
	if (write(1, &"0123456789"[nbr % 10], 1) == -1)
	{
		*ps_len = -1;
		return ;
	}
	++(*ps_len);
}
