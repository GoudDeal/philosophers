/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 13:10:45 by dcyprien          #+#    #+#             */
/*   Updated: 2022/02/21 15:16:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_takes_forks(t_philo *philo)
{
	int	num;

	num = get_num_philo(philo);
	pthread_mutex_lock(philo->var);
	if (num % 2 != 0)
	{
		pthread_mutex_unlock(philo->var);
		philo_takes_forks_odd(philo);
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
		lock_fork_even(philo);
	}
}

void	write_done(t_philo *philo)
{
	pthread_mutex_lock(philo->var);
	pthread_mutex_lock(philo->dead);
	if (philo->done == 0)
	{
		pthread_mutex_lock(philo->lock_output);
		printf("%s%ld%s Philo %s%d%s has finished eating%s\n", BLUE,
			time_passed(*philo->status.starting_time, 1), YELLOW, RED,
			philo->number, WHITE, RESET);
		pthread_mutex_unlock(philo->var);
		philo->done = 1;
		pthread_mutex_unlock(philo->lock_output);
		pthread_mutex_unlock(philo->dead);
	}
	else
	{
		pthread_mutex_unlock(philo->var);
		pthread_mutex_unlock(philo->dead);
	}
}

void	update_action(t_philo *philo, int action)
{
	if (action == SLEEP)
		philo->action = SLEEP;
	if (action == DIE)
		philo->action = DIE;
	if (action == EAT)
		philo->action = EAT;
	if (action == THINK)
		philo->action = THINK;
}

void	set_all_dead(t_philo *philo)
{
	int	num;

	num = get_num_philo(philo);
	pthread_mutex_lock(philo->var);
	while (num >= 1)
	{
		philo->status.all_alive = 0;
		philo = philo->next;
		num--;
	}
	pthread_mutex_unlock(philo->var);
}

void	philo_output(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->lock_output);
	pthread_mutex_lock(philo->var);
	if (philo->status.all_alive == 0 || philo->done)
	{
		pthread_mutex_unlock(philo->var);
		pthread_mutex_unlock(philo->lock_output);
		return ;
	}
	pthread_mutex_unlock(philo->var);
	printf("%s%ld %s%d %s%s%s\n", BLUE, time_passed(*philo->status
			.starting_time, 1), RED, philo->number, WHITE, msg, RESET);
	pthread_mutex_unlock(philo->lock_output);
}
