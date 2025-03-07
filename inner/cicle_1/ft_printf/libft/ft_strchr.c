/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 21:13:37 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/24 23:08:00 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*sub_s;
	unsigned char	sub_c;
	size_t			s_len;
	size_t			i;

	sub_s = (unsigned char *)s;
	s_len = ft_strlen(s);
	sub_c = c;
	i = 0;
	while (i <= s_len)
	{
		if (sub_s[i] == (sub_c))
			return ((char *)&sub_s[i]);
		++i;
	}
	return (0);
}
