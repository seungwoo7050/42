/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 05:38:20 by seungwok          #+#    #+#             */
/*   Updated: 2023/06/23 09:44:17 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "./libft/libft.h"

int		ft_printf(const char *format, ...);
void	parsing_printf(char format, va_list ap, int *ps_len);
void	ft_printf_c(char c, int *ps_len);
void	ft_printf_s(char *s, int *ps_len);
void	ft_printf_p(unsigned long long nbr, int *ps_len, int flag);
void	ft_printf_di(int nbr, int *ps_len);
void	ft_printf_u(unsigned int nbr, int *ps_len);
void	ft_printf_xx(unsigned int nbr, int *ps_len, char flag);

#endif
