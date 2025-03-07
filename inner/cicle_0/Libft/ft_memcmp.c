/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:44:10 by seungwok          #+#    #+#             */
/*   Updated: 2023/05/08 16:50:30 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buf1, const void *buf2, size_t count)
{
	unsigned char	*sub_buf1;
	unsigned char	*sub_buf2;
	size_t			i;

	if (count == 0)
		return (0);
	sub_buf1 = (unsigned char *)buf1;
	sub_buf2 = (unsigned char *)buf2;
	i = 0;
	while (i < count)
	{
		if (sub_buf1[i] != sub_buf2[i] || i + 1 == count)
			break ;
		++i;
	}
	return (sub_buf1[i] - sub_buf2[i]);
}
