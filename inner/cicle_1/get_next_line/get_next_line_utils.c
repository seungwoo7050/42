/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:22:32 by seungwok          #+#    #+#             */
/*   Updated: 2023/07/17 19:38:50 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	str_len;

	str_len = 0;
	while (s[str_len] != 0)
		++str_len;
	return (str_len);
}

char	*ft_strchr(char *s, int c)
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	if (s1 == 0)
	{
		s1 = malloc(sizeof(char));
		if (s1 == 0)
			return (0);
		s1[0] = 0;
	}
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == 0)
		return (free_arr(&s1));
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	j = -1;
	while (s2[++j])
		dest[i + j] = s2[j];
	dest[i + j] = 0;
	free(s1);
	return (dest);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		dst[i] = s[start + i];
		++i;
	}
	dst[i] = 0;
	return (dst);
}
