/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:21:46 by dcyprien          #+#    #+#             */
/*   Updated: 2022/02/21 15:12:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	get_time(t_philo *philo)
{
	pthread_mutex_lock(philo->time_lock);
	gettimeofday(philo->time_last_meal, NULL);
	pthread_mutex_unlock(philo->time_lock);
}

long	time_passed(struct timeval ref, int compare)
{
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	if (compare)
		return ((double)((timer.tv_sec - ref.tv_sec) * 1000)
			+ (long)((timer.tv_usec - ref.tv_usec) * 0.001));
	else
		return ((double)(timer.tv_sec * 1000) + (long)(timer.tv_usec * 0.001));
}

void	sleeps(t_philo *philo, int time)
{
	long int		desired_sleep;
	struct timeval	timer;
	int				timecurr;

	gettimeofday(&timer, NULL);
	desired_sleep = time_passed(timer, 0) + time;
	while (time_passed(timer, 0) < desired_sleep)
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
}

int	check_all_alive(t_philo *philo)
{
	int	num;
	int	i;

	i = 0;
	num = get_num_philo(philo);
	while (philo->number != 1)
		philo = philo->prev;
	while (philo->number != num)
	{
		pthread_mutex_lock(philo->var);
		if (philo->status.all_alive == 0)
			i++;
		pthread_mutex_unlock(philo->var);
		philo = philo->next;
	}
	if (i > 0)
		pthread_mutex_lock(philo->var);
	return (i);
}

void	philo_does(t_philo *philo)
{
	pthread_mutex_lock(philo->var);
	while (philo->status.all_alive && philo->done == 0)
	{
		pthread_mutex_unlock(philo->var);
		if (philo->action == EAT && philo->status.all_alive)
			philo_eats(philo);
		if (check_all_alive(philo))
			break ;
		if (philo->number_of_eat == 0)
			write_done(philo);
		if (philo->action == SLEEP && philo->status.all_alive)
			philo_sleep(philo);
		if (check_all_alive(philo))
			break ;
		if (philo->action == THINK && philo->status.all_alive)
			philo_thinks(philo);
		if (check_all_alive(philo))
			break ;
		pthread_mutex_lock(philo->var);
	}
	pthread_mutex_unlock(philo->var);
}
