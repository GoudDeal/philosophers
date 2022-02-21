/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:57:52 by dcyprien          #+#    #+#             */
/*   Updated: 2022/02/15 16:50:03 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	pthread_mutex_lock(philo->var);
	while (!philo->status.all_started)
	{
		pthread_mutex_unlock(philo->var);
		usleep(500);
		pthread_mutex_lock(philo->var);
	}
	pthread_mutex_unlock(philo->var);
	philo_does(philo);
	return (NULL);
}

void	create_threads(t_philo *philo, int num)
{
	philo->dead = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->dead, NULL);
	while (num >= 1)
	{
		pthread_create(&philo->thread, NULL, &start_routine, (void *)philo);
		philo = philo->next;
		philo->dead = philo->prev->dead;
		num--;
	}
	num = get_num_philo(philo);
	while (num >= 1)
	{
		pthread_mutex_lock(philo->var);
		philo->status.all_started = 1;
		pthread_mutex_unlock(philo->var);
		philo = philo->next;
		num--;
	}
	num = get_num_philo(philo);
	while (num >= 1)
	{
		pthread_join(philo->prev->thread, NULL);
		philo = philo->next;
		num--;
	}
}
