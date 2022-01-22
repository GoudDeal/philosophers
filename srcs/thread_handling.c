/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:57:52 by dcyprien          #+#    #+#             */
/*   Updated: 2022/01/22 17:46:23 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*placeholder(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("number = %d\n", philo->number);
	pthread_mutex_init(philo->mutex, NULL);
	return (NULL);
}

void	create_threads(t_philo *philo, int num)
{
	while (num >= 1)
	{
		pthread_create(&philo->thread, NULL, &placeholder, (void*)philo);
		philo = philo->next;
		pthread_join(philo->prev->thread, NULL);
		num--;
	}
}
