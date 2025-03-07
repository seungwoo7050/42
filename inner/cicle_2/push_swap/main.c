/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:37:19 by seungwok          #+#    #+#             */
/*   Updated: 2023/10/31 20:10:59 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_arr(t_info **info)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < ((*info)->size) - 1)
	{
		j = i + 1;
		while (j < ((*info)->size))
		{
			if ((*info)->arr[i] > (*info)->arr[j])
			{
				tmp = (*info)->arr[i];
				(*info)->arr[i] = (*info)->arr[j];
				(*info)->arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	convert_index(t_info **info)
{
	int		i;
	t_stack	*cur;

	sort_arr(info);
	cur = (*info)->a_head;
	while (cur)
	{
		i = 0;
		while (cur->val != (*info)->arr[i])
			i++;
		cur->val = i;
		cur = cur->below;
	}
}

void	init_stack(t_info **info)
{
	int		i;
	t_stack	*cur;

	(*info)->a_head = (t_stack *)malloc(sizeof(t_stack));
	if (!((*info)->a_head))
		exit (1);
	(*info)->a_head->above = 0;
	cur = (*info)->a_head;
	i = -1;
	while (++i < (*info)->size)
	{
		cur->val = (*info)->arr[i];
		if (i == ((*info)->size) - 1)
			break ;
		cur->below = (t_stack *)malloc(sizeof(t_stack));
		if (!(cur->below))
			exit(1);
		cur->below->above = cur;
		cur = cur->below;
	}
	cur->below = 0;
	(*info)->a_tail = cur;
	(*info)->b_head = 0;
	(*info)->b_tail = 0;
}

int	main(int ac, char **av)
{
	t_info	*info;
	t_stack	*cur;
	t_stack	*tmp;

	if (ac < 2)
		exit (1);
	inspect_av(av, &info);
	init_stack(&info);
	convert_index(&info);
	sort_start(&info);
	cur = info->a_head;
	while (cur)
	{
		tmp = cur->below;
		free(cur);
		cur = tmp;
	}
	free(info->arr);
	free(info);
	return (0);
}

	// // 스택확인과정
	// t_stack *cur;
	// cur = info->a_head;
	// printf("A: ");
	// while(cur)
	// {	
	// 	printf("%d ", cur->val);
	// 	cur = cur->below;
	// }
	// if (info->a_head)
	// 	printf("\nhead: %d\ntail: %d\n", info->a_head->val, info->a_tail->val);
	// else
	// 	printf("NULL\n");
	// cur = info->b_head;
	// printf("B: ");
	// while(cur)
	// {	
	// 	printf("%d ", cur->val);
	// 	cur = cur->below;
	// }
	// if (info->b_head)
	// 	printf("head: %d\ntail: %d\n", info->b_head->val, info->b_tail->val);
	// else
	// 	printf("NULL");
	// return (0);

	// // 메모리누수 확인
	// void	check_leaks(void)
	// {
	// 	system("leaks push_swap");
	// }

	// atexit(check_leaks);
