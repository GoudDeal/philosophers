/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:32:25 by dcyprien          #+#    #+#             */
/*   Updated: 2022/02/21 15:24:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	lock_fork_even(t_philo *philo)
{
	pthread_mutex_lock(philo->prev_fork);
	philo_output(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork);
	philo_output(philo, "has taken a fork");
}

void	lock_fork_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->fork);
	philo_output(philo, "has taken a fork");
	pthread_mutex_lock(philo->prev_fork);
	philo_output(philo, "has taken a fork");
}

void	philo_takes_forks_odd(t_philo *philo)
{
	int	num;
	int	way;

	way = 0;
	num = get_num_philo(philo);
	if (philo->number == 1)
	{
		if (way == 0)
		{
			lock_fork_even(philo);
			way = 1;
		}
		else
			lock_fork_odd(philo);
		return ;
	}
	if (philo->number % 2 == 0 && philo->number != num)
		lock_fork_even(philo);
	else if (philo->number % 2 != 0)
	{
		if (philo->number != num)
			lock_fork_odd(philo);
	}
	if (philo->number == num)
	{
		lock_fork_odd(philo);
	}
	pthread_mutex_unlock(philo->var);
}