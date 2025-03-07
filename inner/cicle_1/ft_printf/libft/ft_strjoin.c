/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:35:16 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/25 00:01:12 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;
	size_t		str_len;
	size_t		i;

	str_len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(sizeof(char) * (str_len + 1));
	if (dest == 0)
		return (0);
	str_len = 0;
	while (s1[str_len])
	{
		dest[str_len] = s1[str_len];
		++str_len;
	}
	i = 0;
	while (s2[i])
		dest[str_len++] = s2[i++];
	dest[str_len] = 0;
	return (dest);
}

//s1과 s2를 이어붙인 뒤 만든 문자열의 시작주소를 반환.