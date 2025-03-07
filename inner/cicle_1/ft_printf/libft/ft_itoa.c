/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 22:38:53 by seungwok          #+#    #+#             */
/*   Updated: 2023/03/26 05:59:15 by seungwok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countdigit(int n)
{
	int	digit;

	digit = 0;
	if (n < 0)
	{
		digit += 1;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		digit += 1;
	}
	return (digit);
}

void	ft_nbrdup(int n, int digit, char *nbr)
{
	if (n < 0)
	{
		*nbr = '-';
		n *= -1;
	}
	if (n > 0)
	{
		nbr[digit - 1] = n % 10 + '0';
		ft_nbrdup(n / 10, digit - 1, nbr);
	}
}

char	*ft_exception_handling_for_itoa(int n)
{
	char	*nbr;

	if (n == -2147483648)
	{
		nbr = (char *)malloc(sizeof(char) * 12);
		if (nbr == 0)
			return (0);
		nbr[0] = '-';
		nbr[1] = '2';
		n = 147483648;
		ft_nbrdup(n, 9, nbr + 2);
		nbr[11] = 0;
	}
	else
	{
		nbr = (char *)malloc(sizeof(char) * 2);
		if (nbr == 0)
			return (0);
		nbr[0] = '0';
		nbr[1] = 0;
	}
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		digit;

	if (n == 0 || n == -2147483648)
	{
		nbr = ft_exception_handling_for_itoa(n);
		return (nbr);
	}
	digit = ft_countdigit(n);
	nbr = (char *)malloc(sizeof(char) * (digit + 1));
	if (nbr == 0)
		return (0);
	ft_nbrdup(n, digit, nbr);
	nbr[digit] = 0;
	return (nbr);
}
