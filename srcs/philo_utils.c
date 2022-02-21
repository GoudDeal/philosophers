/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:42:38 by dcyprien          #+#    #+#             */
/*   Updated: 2022/02/21 15:11:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_num_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->number >= i)
	{
		i = philo->number;
		philo = philo->next;
	}
	return (i);
}

void	exit_philo(t_philo *philo)
{
	int	num;

	num = get_num_philo(philo);
	while (num >= 1)
	{
		philo->status.all_alive = 0;
		philo = philo->next;
		num--;
	}
}

int	verify_alive(t_philo *philo)
{
	long	time;
	pthread_mutex_lock(philo->time_lock);
	time = time_passed(*philo->time_last_meal, 1);
	pthread_mutex_unlock(philo->time_lock);
	pthread_mutex_lock(philo->var);
	if (time > philo->time_to_die && philo->status.all_alive != 0)
	{
		pthread_mutex_unlock(philo->var);
		pthread_mutex_lock(philo->dead);
		philo->status.all_alive = 0;
		philo_dies(philo);
		set_all_dead(philo);
		pthread_mutex_unlock(philo->dead);
		return (1);
	}
	pthread_mutex_unlock(philo->var);
	return (0);
}
