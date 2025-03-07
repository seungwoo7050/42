/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:32:05 by seungwok          #+#    #+#             */
/*   Updated: 2023/12/03 10:37:16 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	convert_time(struct timeval time)
{
	long long	val;

	val = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (val);
}

int	atoi_philo(char *str)
{
	int	val;

	val = 0;
	if (str[0] > '9' || str[0] < '0')
		exit (1);
	while (*str >= '0' && *str <= '9')
	{
		val = val * 10 + (*str - '0');
		str++;
	}
	if (*str)
		exit (1);
	return (val);
}

int	print_philo(t_philo *p, int i, long long time)
{
	pthread_mutex_lock(&p->arg->printf);
	if (i == 1 && check_lifesign(p))
		printf("%llu %d has taken a fork\n", time, p->id);
	else if (i == 2 && check_lifesign(p))
		printf("%llu %d is sleeping\n", time, p->id);
	else if (i == 3 && check_lifesign(p))
		printf("%llu %d is thinking\n", time, p->id);
	else if (i == 4 && check_lifesign(p))
		printf("%llu %d is eating\n", time, p->id);
	else if (i == 5 && check_lifesign(p))
	{
		pthread_mutex_lock(&p->arg->m_life_sign);
		p->arg->life_sign = 0;
		pthread_mutex_unlock(&p->arg->m_life_sign);
		printf("%llu %d died\n", time, p->id);
		pthread_mutex_unlock(&p->arg->printf);
		return (0);
	}
	pthread_mutex_unlock(&p->arg->printf);
	return (1);
}
