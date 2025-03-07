/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:47:55 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/15 10:07:59 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		str_len;
	int		i;

	str_len = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (str_len + 1));
	if (dest == 0)
		return (0);
	i = 0;
	while (s[i] != 0)
	{
		dest[i] = s[i];
		++i;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - (size_t)start)
		len = ft_strlen(s) - (size_t)start;
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

int	split_iteration(char **dest, const char *s, char c, int count)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (j < count)
	{
		while (s[i] == c)
			++i;
		start = i;
		while (s[i] != c && s[i] != 0)
			++i;
		dest[j] = ft_substr(s, start, i - start);
		if (dest[j] == 0)
		{
			split_free(dest, j);
			return (1);
		}
		++j;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**dest;

	i = 0;
	count = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			++count;
		++i;
	}
	dest = (char **)malloc(sizeof(char *) * (count + 1));
	if (dest == 0)
		return (0);
	if (split_iteration(dest, s, c, count) == 1)
		return (0);
	dest[count] = 0;
	return (dest);
}

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
