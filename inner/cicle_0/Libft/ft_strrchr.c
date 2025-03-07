/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:16:55 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/24 23:08:53 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*sub_s;
	unsigned char	sub_c;
	size_t			i;

	sub_s = (unsigned char *)s;
	sub_c = c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (sub_c) || i == 0)
			break ;
		--i;
	}
	if (s[i] != sub_c)
		return (0);
	return ((char *)&sub_s[i]);
}
