/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 21:14:56 by seungwok          #+#    #+#             */
/*   Updated: 2023/12/03 10:37:23 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	loner_pilo(t_philo *p)
{
	pthread_mutex_unlock(&p->m_fork);
	while (1)
	{
		if (!cal_life(p))
			return (0);
		usleep(200);
	}
}

int	philo_is_eat(t_philo *p)
{	
	struct timeval	t_cur;
	long long		cur;

	if (!take_forks(p))
		return (0);
	gettimeofday(&t_cur, NULL);
	cur = convert_time(t_cur);
	if (!print_philo(p, 4, cur - p->start_time))
		return (0);
	p->last_meal = cur;
	while (1)
	{
		if (!cal_life(p))
			return (take_back_forks(p));
		gettimeofday(&t_cur, NULL);
		if (convert_time(t_cur) - cur >= p->time_to_eat)
			break ;
		usleep(100 + p->num_philo);
	}
	if (!take_back_forks(p))
		return (0);
	return (1);
}

int	philo_is_sleep(t_philo *p)
{
	struct timeval	t_cur;
	long long		cur;

	gettimeofday(&t_cur, NULL);
	cur = convert_time(t_cur);
	if (!print_philo(p, 2, cur - p->start_time))
		return (0);
	while (1)
	{
		if (!cal_life(p))
			return (0);
		gettimeofday(&t_cur, NULL);
		if (convert_time(t_cur) - cur >= p->time_to_eat)
			break ;
		usleep(200);
	}
	return (1);
}

int	philo_is_think(t_philo *p)
{
	struct timeval	t_cur;
	long long		cur;

	gettimeofday(&t_cur, NULL);
	cur = convert_time(t_cur);
	if (!print_philo(p, 3, cur - p->start_time))
		return (0);
	return (1);
}

void	*philosopher(void *pointer)
{
	t_philo	*p;

	p = (t_philo *)pointer;
	if (p->id % 2 == 1)
		usleep(200 + p->num_philo);
	while (1)
	{
		if (philo_is_eat(p))
		{
			if (!p->max_meals)
				break ;
			if (!philo_is_sleep(p))
				break ;
			if (!philo_is_think(p))
				break ;
		}
		if (!cal_life(p))
			break ;
	}
	return (0);
}
