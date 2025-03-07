/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:49:24 by seungwok          #+#    #+#             */
/*   Updated: 2023/12/01 15:29:12 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing_arg(int ac, char **av, t_arg *p)
{
	struct timeval	cur;

	if (ac < 5 || ac > 6)
		exit (1);
	p->life_sign = 1;
	p->num_philo = atoi_philo(av[1]);
	p->time_to_live = atoi_philo(av[2]);
	p->time_to_eat = atoi_philo(av[3]);
	p->time_to_sleep = atoi_philo(av[4]);
	if (ac == 6)
		p->max_meals = atoi_philo(av[5]);
	else
		p->max_meals = -1;
	gettimeofday(&cur, NULL);
	p->start_time = convert_time(cur);
	pthread_mutex_init(&p->printf, NULL);
	pthread_mutex_init(&p->m_life_sign, NULL);
}

t_philo	*init_philo(t_arg *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)malloc(sizeof(t_philo) * arg->num_philo);
	i = -1;
	while (++i < arg->num_philo)
	{		
		philo[i].num_philo = arg->num_philo;
		philo[i].id = i + 1;
		philo[i].fork = 0;
		philo[i].max_meals = arg->max_meals;
		philo[i].time_to_live = arg->time_to_live;
		philo[i].time_to_eat = arg->time_to_eat;
		philo[i].time_to_sleep = arg->time_to_sleep;
		philo[i].start_time = arg->start_time;
		philo[i].last_meal = arg->start_time;
		philo[i].arg = arg;
		pthread_mutex_init(&philo[i].m_fork, NULL);
	}
	return (philo);
}
