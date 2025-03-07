/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:46:33 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/25 17:01:30 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	int		start;
	int		end;
	int		i;

	i = 0;
	while (s1[i] != 0 && ft_strchr(set, s1[i]) != 0)
		++i;
	start = i;
	i = (int)ft_strlen(s1) - 1;
	while (i >= 0 && ft_strchr(set, s1[i]) != 0)
		--i;
	end = i;
	if (start > end)
		return (ft_strdup(""));
	dst = (char *)malloc(sizeof(char) * (end - start + 2));
	if (dst == 0)
		return (0);
	ft_strlcpy(dst, &s1[start], end - start + 2);
	return (dst);
}
