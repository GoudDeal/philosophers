/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:37:39 by dcyprien          #+#    #+#             */
/*   Updated: 2022/02/16 18:06:46 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	go_to_first_philo(t_philo **philo)
{
	while ((*philo)->number != 1)
		(*philo) = (*philo)->prev;
}

void	set_values(t_philo **philo, int index, char **av)
{
	(*philo)->time_last_meal = malloc(sizeof(struct timeval));
	(*philo)->time_last_meal->tv_usec = 0;
	(*philo)->time_last_meal->tv_sec = 0;
	gettimeofday((*philo)->time_last_meal, NULL);
	(*philo)->thread = 0;
	(*philo)->number = index;
	(*philo)->done = 0;
	(*philo)->time_to_die = ft_atoi(av[2]);
	(*philo)->time_to_eat = ft_atoi(av[3]);
	(*philo)->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		(*philo)->number_of_eat = ft_atoi(av[5]);
	else
		(*philo)->number_of_eat = -1;
	(*philo)->next = NULL;
	(*philo)->prev = NULL;
	if ((*philo)->number % 2 == 0)
		(*philo)->action = EAT;
	else
		(*philo)->action = SLEEP;
}

t_status	*init_status(void)
{
	t_status	*status;

	status = malloc(sizeof(t_status));
	status->starting_time = malloc(sizeof(struct timeval));
	status->starting_time->tv_sec = 0;
	status->starting_time->tv_usec = 0;
	gettimeofday(status->starting_time, NULL);
	status->all_alive = 1;
	status->all_started = 0;
	return (status);
}

void	init_mutex(t_philo *philo, int num)
{
	go_to_first_philo(&philo);
	philo->lock_output = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->var = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	philo->time_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->time_lock, NULL);
	pthread_mutex_init(philo->lock_output, NULL);
	pthread_mutex_init(philo->var, NULL);
	while (num >= 0)
	{
		philo->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo->fork, NULL);
		philo = philo->next;
		philo->lock_output = philo->prev->lock_output;
		philo->var = philo->prev->var;
		philo->time_lock = philo->prev->time_lock;
		philo->prev_fork = philo->prev->fork;
		num--;
	}
}

t_philo	*init_philos(char **av, int num, t_status **tmpbis)
{
	t_philo		*new;
	t_philo		*first;
	t_philo		*tmp;
	t_status	*status;

	first = malloc(sizeof(t_philo));
	status = init_status();
	*tmpbis = status;
	set_values(&first, 1, av);
	new = first;
	tmp = first;
	while (--num >= 0)
	{
		new->status = *status;
		new->next = malloc(sizeof(t_philo));
		set_values(&new->next, ft_atoi(av[1]) - num, av);
		new = new->next;
		new->prev = tmp;
		tmp = new;
	}
	new->status = *status;
	new->next = first;
	first->prev = new;
	init_mutex(first, ft_atoi(av[1]) - 1);
	return (first);
}
