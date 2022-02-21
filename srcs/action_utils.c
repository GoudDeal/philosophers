/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 13:10:45 by dcyprien          #+#    #+#             */
/*   Updated: 2022/02/21 15:58:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



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
		long	timecurr;
	
	pthread_mutex_lock(philo->var);
	timecurr = time_passed(*philo->time_last_meal, 1);
	if (timecurr > philo->time_to_die && philo->status.all_alive != 0)
	{
		pthread_mutex_unlock(philo->var);
		philo_dies(philo);
		set_all_dead(philo);
		return ;
	}
	if (philo->status.all_alive == 0 || philo->done)
	{
		pthread_mutex_unlock(philo->var);
		pthread_mutex_unlock(philo->lock_output);
		return ;
	}
	pthread_mutex_lock(philo->lock_output);
	pthread_mutex_unlock(philo->var);
	printf("%s%ld %s%d %s%s%s\n", BLUE, time_passed(*philo->status
			.starting_time, 1), RED, philo->number, WHITE, msg, RESET);
	pthread_mutex_unlock(philo->lock_output);
}
