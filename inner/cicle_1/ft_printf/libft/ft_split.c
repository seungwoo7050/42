/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:47:18 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/28 21:47:24 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
