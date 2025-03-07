/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:49:24 by seungwok          #+#    #+#             */
/*   Updated: 2023/12/03 10:37:21 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pickup_fork(t_philo *p, int c)
{
	struct timeval	t_cur;

	if (!check_lifesign(p))
		return (0);
	pthread_mutex_lock(&(p + c)->m_fork);
	(p + c)->fork = 1;
	gettimeofday(&t_cur, NULL);
	if (!print_philo(p, 1, convert_time(t_cur) - p->start_time))
		return (0);
	return (1);
}

int	putdown_fork(t_philo *p, int c)
{
	if (!check_lifesign(p))
	{
		pthread_mutex_unlock(&(p + c)->m_fork);
		return (0);
	}
	(p + c)->fork = 0;
	pthread_mutex_unlock(&(p + c)->m_fork);
	return (1);
}

int	take_forks(t_philo *p)
{
	int				c;

	c = 1;
	if (p->num_philo == p->id)
		c = (p->id - 1) * -1;
	if (!pickup_fork(p, 0))
		return (0);
	if (p->num_philo == 1)
		return (loner_pilo(p));
	if (!pickup_fork(p, c))
	{
		putdown_fork(p, 0);
		return (0);
	}
	return (1);
}

int	take_back_forks(t_philo *p)
{
	int				c;

	c = 1;
	if (p->num_philo == p->id)
	c = (p->id - 1) * -1;
	if (!putdown_fork(p, c))
	{
		pthread_mutex_unlock(&p->m_fork);
		return (0);
	}
	if (!putdown_fork(p, 0))
		return (0);
	p->max_meals--;
	return (1);
}
