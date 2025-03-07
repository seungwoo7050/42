/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:30:09 by seungwok          #+#    #+#             */
/*   Updated: 2023/12/03 10:37:23 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_lifesign(t_philo *p)
{
	pthread_mutex_lock(&p->arg->m_life_sign);
	if (p->arg->life_sign)
	{
		pthread_mutex_unlock(&p->arg->m_life_sign);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&p->arg->m_life_sign);
		return (0);
	}
}

int	cal_life(t_philo *p)
{
	struct timeval	t_cur;
	long long		cur;

	if (!check_lifesign(p))
		return (0);
	gettimeofday(&t_cur, NULL);
	cur = convert_time(t_cur);
	if (cur - p->last_meal >= p->time_to_live)
		return (print_philo(p, 5, cur - p->start_time));
	return (1);
}
