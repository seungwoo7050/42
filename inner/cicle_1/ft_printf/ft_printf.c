/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 04:52:02 by seungwok          #+#    #+#             */
/*   Updated: 2023/07/14 17:05:58 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		s_len;
	va_list	ap;

	s_len = 0;
	va_start(ap, format);
	while (*format != 0)
	{
		if (*format == '%')
		{
			++format;
			parsing_printf(*format, ap, &s_len);
		}
		else
			ft_printf_c(*format, &s_len);
		if (s_len == -1)
			return (-1);
		++format;
	}
	va_end(ap);
	return (s_len);
}

void	parsing_printf(char format, va_list ap, int *ps_len)
{
	if (format == 'c')
		ft_printf_c(va_arg(ap, int), ps_len);
	else if (format == 's')
		ft_printf_s(va_arg(ap, char *), ps_len);
	else if (format == 'p')
		ft_printf_p(va_arg(ap, unsigned long long), ps_len, 1);
	else if (format == 'd' || format == 'i')
		ft_printf_di(va_arg(ap, int), ps_len);
	else if (format == 'u')
		ft_printf_u(va_arg(ap, unsigned int), ps_len);
	else if (format == 'x')
		ft_printf_xx(va_arg(ap, int), ps_len, 'x');
	else if (format == 'X')
		ft_printf_xx(va_arg(ap, int), ps_len, 'X');
	else if (format == '%')
	{
		if (write(1, "%", 1) == -1)
		{
			*ps_len = -1;
			return ;
		}
		++(*ps_len);
	}
}
