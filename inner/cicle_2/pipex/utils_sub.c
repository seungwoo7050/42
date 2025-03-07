/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:03:35 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/13 11:16:06 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	str_len;

	str_len = 0;
	while (s[str_len] != 0)
		++str_len;
	return (str_len);
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && i + 1 < n && s1[i] != 0)
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
