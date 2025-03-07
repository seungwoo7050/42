/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:42:38 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 16:16:56 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	ft_strlen(const char *s)
{
	size_t	str_len;

	str_len = 0;
	while (s[str_len] != 0)
		++str_len;
	return (str_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

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

void	split_free(char **dest, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free (dest[i]);
		++i;
	}
	free (dest);
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
