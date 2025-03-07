/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:33:00 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/20 19:10:27 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
