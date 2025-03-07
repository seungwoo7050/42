/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 06:48:24 by seungwok          #+#    #+#             */
/*   Updated: 2023/06/24 22:59:20 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_c(char c, int *s_len)
{
	if ((write (1, &c, 1)) == -1)
	{
		*s_len = -1;
		return ;
	}
	++(*s_len);
}

void	ft_printf_s(char *s, int *ps_len)
{
	size_t	s_len;

	if (s == 0)
	{
		if (write(1, "(null)", 6) == -1)
		{
			*ps_len = -1;
			return ;
		}
		*ps_len += 6;
		return ;
	}
	s_len = ft_strlen(s);
	if (write (1, s, s_len) == -1)
	{
		*ps_len = -1;
		return ;
	}
	*ps_len += s_len;
}
