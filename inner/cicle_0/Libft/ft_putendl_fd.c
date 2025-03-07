/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:50:22 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/19 22:01:16 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	str_len;

	str_len = 0;
	if (fd < 0 || s == 0)
		return ;
	str_len = ft_strlen(s);
	write(fd, s, str_len);
	write(fd, "\n", 1);
}
