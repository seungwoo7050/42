/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungwok <seungwok@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:25:22 by seungwok          #+#    #+#             */
/*   Updated: 2023/11/19 17:25:22 by seungwok         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_arg	arg;
	t_philo	*philo;
	int		i;

	parsing_arg(ac, av, &arg);
	philo = init_philo(&arg);
	i = -1;
	while (++i < arg.num_philo)
		pthread_create(&philo[i].thread, NULL, philosopher, (void *)&philo[i]);
	i = -1;
	while (++i < arg.num_philo)
		pthread_join(philo[i].thread, NULL);
	i = -1;
	while (++i < arg.num_philo)
		pthread_mutex_destroy(&philo[i].m_fork);
	pthread_mutex_destroy(&arg.m_life_sign);
	pthread_mutex_destroy(&arg.printf);
	free(philo);
	return (0);
}
