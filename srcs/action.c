/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:07:31 by dcyprien          #+#    #+#             */
/*   Updated: 2022/02/21 16:08:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(philo->prev_fork);
}

void	philo_dies(t_philo *philo)
{
	int	num;
	int	i;

	i = 0;
	pthread_mutex_lock(philo->var);
	philo->status.all_alive = 0;
	num = get_num_philo(philo);
	while (num >= 1)
	{
		if (philo->status.all_alive == 0)
			i++;
		philo = philo->next;
		num--;
	}
	if (i == 1)
	{
		pthread_mutex_unlock(philo->var);
		pthread_mutex_lock(philo->lock_output);
		printf("%s%ld %s%d %sdied%s\n", BLUE, time_passed(*philo->status
				.starting_time, 1), RED, philo->number, WHITE, RESET);
		pthread_mutex_unlock(philo->lock_output);
	}
	else
		pthread_mutex_unlock(philo->var);
	update_action(philo, DIE);
}

void	philo_thinks(t_philo *philo)
{
	struct timeval	timer;
	long int		desired_think;
	int				timecurr;

	gettimeofday(&timer, NULL);
	desired_think = time_passed(timer, 0)
		+ (philo->time_to_eat - philo->time_to_sleep);
	while (time_passed(timer, 0) < desired_think)
	{
		timecurr = time_passed(*philo->time_last_meal, 1);
		pthread_mutex_lock(philo->var);
		if (timecurr > philo->time_to_die && philo->status.all_alive != 0)
		{
			pthread_mutex_unlock(philo->var);
			philo_dies(philo);
			set_all_dead(philo);
			break ;
		}
		pthread_mutex_unlock(philo->var);
		usleep(500);
	}
	pthread_mutex_unlock(philo->var);
	philo_output(philo, "is thinking");
	update_action(philo, EAT);
	pthread_mutex_lock(philo->var);
	if (philo->time_to_sleep < philo->time_to_eat && philo->number % 2 != 0)
	{
		pthread_mutex_unlock(philo->var);
		sleeps(philo, (philo->time_to_eat - philo->time_to_sleep) + 1);
	}
	pthread_mutex_unlock(philo->var);
}

void	philo_eats(t_philo *philo)
{
	philo_takes_forks(philo);
	philo_output(philo, "is eating");
	gettimeofday(philo->time_last_meal, NULL);
	philo->number_of_eat -= 1;
	sleeps(philo, philo->time_to_eat);
	unlock_forks(philo);
	update_action(philo, SLEEP);
}

void	philo_sleep(t_philo *philo)
{
	philo_output(philo, "is sleeping");
	update_action(philo, THINK);
	sleeps(philo, philo->time_to_sleep);
}
