/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:05:04 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 18:23:53 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_info(t_info **info)
{
	(*info) = (t_info *)malloc(sizeof(t_info));
	if (!(*info))
		print_error ();
	(*info)->size = 0;
}

void	cal_size(t_info **info, char **av)
{
	int		i;
	int		j;
	int		size;
	char	**tmp;

	size = (*info)->size;
	i = 0;
	while (av[++i])
	{
		j = -1;
		tmp = ft_split(av[i], ' ');
		while (tmp[++j])
			((*info)->size)++;
		split_free(tmp, --j);
	}
	size = (*info)->size;
	(*info)->arr = (int *)malloc(sizeof(int) * (*info)->size);
}

void	check_sort_dup(t_info **info)
{
	int	i;
	int	j;
	int	sign;

	i = 0;
	sign = 0;
	while (i < (((*info)->size) - 1))
	{
		if ((*info)->arr[i] > (*info)->arr[i + 1])
			sign = 1;
		j = i + 1;
		while (j < ((*info)->size))
			if ((*info)->arr[i] == (*info)->arr[j++])
				print_error ();
		i++;
	}
	if (sign == 0)
		exit (1);
}

void	check_space(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = 0;
		while (av[i][j] == ' ')
			j++;
		if (!(av[i][j]))
			print_error ();
	}
}

void	inspect_av(char **av, t_info **info)
{
	int		i;
	int		j;
	int		k;
	char	**tmp;

	set_info(info);
	check_space(av);
	cal_size(info, av);
	i = 0;
	k = -1;
	while (av[++i])
	{
		tmp = ft_split(av[i], ' ');
		j = -1;
		while (tmp[++j])
			(*info)->arr[++k] = ft_atoi(tmp[j]);
		split_free(tmp, j);
	}
	check_sort_dup(info);
}
