/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:25:23 by seungwok          #+#    #+#             */
/*   Updated: 2023/05/08 15:27:01 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*sub_dest;
	char	*sub_src;
	size_t	i;

	if (dest == 0 && src == 0)
		return (0);
	sub_dest = (char *)dest;
	sub_src = (char *)src;
	i = 0;
	while (i < n)
	{
		sub_dest[i] = sub_src[i];
		++i;
	}
	return (dest);
}
