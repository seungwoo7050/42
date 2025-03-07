/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:30:40 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/24 21:25:29 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*sub_dest;
	unsigned char	*sub_src;
	size_t			i;

	if (n == 0 || dest == src)
		return (dest);
	sub_dest = (unsigned char *)dest;
	sub_src = (unsigned char *)src;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			sub_dest[i] = sub_src[i];
			++i;
		}
	}
	else
	{
		while (n-- > 0)
			sub_dest[n] = sub_src[n];
	}
	return (dest);
}
