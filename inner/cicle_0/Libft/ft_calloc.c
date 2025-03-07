/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:26:11 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/24 23:24:59 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*arr;

	arr = (void *)malloc(size * num);
	if (arr == NULL)
		return (0);
	ft_memset(arr, 0, (size * num));
	return (arr);
}
//num * size 만큼 메모리를 할당한 뒤 0으로 채운다