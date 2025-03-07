/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:20:40 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/18 23:08:43 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	int		s_len;
	int		i;

	s_len = ft_strlen(s);
	dst = (char *)malloc(sizeof(char) * (s_len + 1));
	if (dst == 0)
		return (0);
	i = 0;
	while (s[i] != 0)
	{
		dst[i] = f(i, s[i]);
		i += 1;
	}
	dst[i] = 0;
	return (dst);
}
