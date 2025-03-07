/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   philo.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: seungwok <seungwok@student.42seoul.kr>	 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/24 21:31:55 by seungwok		  #+#	#+#			 */
/*   Updated: 2023/11/24 21:31:55 by seungwok		 ###   ########seoul.kr  */
/*																			*/
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_arg
{
	int				life_sign;
	int				num_philo;
	int				max_meals;
	long long		time_to_live;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	pthread_mutex_t	printf;
	pthread_mutex_t	m_life_sign;
}	t_arg;

typedef struct s_philo
{
	pthread_t		thread;
	int				num_philo;
	int				id;
	int				fork;
	int				max_meals;
	long long		time_to_live;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		start_time;
	long long		last_meal;
	pthread_mutex_t	m_fork;
	t_arg			*arg;
}	t_philo;

// parsing.c
void		parsing_arg(int ac, char **av, t_arg *p);
t_philo		*init_philo(t_arg *arg);

// iter.c
int			loner_pilo(t_philo *p);
int			philo_is_eat(t_philo *philo);
int			philo_is_sleep(t_philo *philo);
int			philo_is_think(t_philo *philo);
void		*philosopher(void *arg);

// fork.c
int			pickup_fork(t_philo *philo, int c);
int			putdown_fork(t_philo *philo, int c);
int			take_forks(t_philo *philo);
int			take_back_forks(t_philo *philo);

// life.c
int			cal_life(t_philo *p);
int			check_lifesign(t_philo *p);

// utils.c
int			atoi_philo(char *str);
long long	convert_time(struct timeval time);
int			print_philo(t_philo *philo, int i, long long time);

#endif