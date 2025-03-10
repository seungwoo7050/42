/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 20:19:17 by seungwok          #+#    #+#             */
/*   Updated: 2023/05/08 15:25:09 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*sub_s;

	i = 0;
	sub_s = (unsigned char *)s;
	while (i < n)
	{
		sub_s[i] = 0;
		++i;
	}
}
