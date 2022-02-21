/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_unlock.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:11:04 by dcyprien          #+#    #+#             */
/*   Updated: 2022/02/15 18:28:13 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_the_mutex(t_philo *philo)
{
	int	num;

	num = get_num_philo(philo);
	pthread_mutex_lock(philo->var);
	while (philo->number != 1)
		philo = philo->prev;
	while (num >= 1)
	{
		if (philo->fork)
		{
			pthread_mutex_destroy(philo->fork);
			free(philo->fork);
			philo->fork = NULL;
		}
		philo = philo->next;
		num--;
	}
	pthread_mutex_unlock(philo->var);
	pthread_mutex_destroy(philo->dead);
	pthread_mutex_destroy(philo->var);
	pthread_mutex_destroy(philo->lock_output);
}

void	free_status(t_philo *philo, int num)
{
	while (philo->number != 1)
		philo = philo->prev;
	while (philo->number != num)
	{
		free(philo->time_last_meal);
		philo = philo->next;
	}
	free(philo->time_last_meal);
}

void	free_them_all(t_philo *philo)
{
	int		i;
	t_philo	*next;

	i = get_num_philo(philo);
	next = philo->next;
	free_status(philo, i);
	while (philo->number != 1)
	{
		philo = philo->prev;
		next = philo->next;
	}
	while (i > 1)
	{
		free(philo);
		philo = next;
		next = next->next;
		i--;
	}
	free(philo->var);
	free(philo->time_lock);
	free(philo->dead);
	free(philo->lock_output);
	free(philo->fork);
	free(philo);
}
