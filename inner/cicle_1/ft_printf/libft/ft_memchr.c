/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:26:45 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/19 23:33:53 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t count)
{
	size_t			i;
	unsigned char	*sub_buf;
	unsigned char	sub_c;

	i = 0;
	sub_c = c;
	sub_buf = (unsigned char *)buf;
	while (i < count)
	{
		if (sub_buf[i] == sub_c)
			break ;
		i += 1;
	}
	if (i == count)
		return (0);
	return ((void *)&buf[i]);
}

//buf에서 c찾기