/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:57:19 by dcyprien          #+#    #+#             */
/*   Updated: 2022/01/22 15:53:17 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	verify_all(t_philo *philo, int num)
{
	int		i;
	t_philo	*curr;

	curr = philo;
	i = 0;
	while (i < num)
	{
		printf("thread = %lu\n", curr->thread);
		printf("number = %d\n", curr->number);
		printf("time to die = %d\n", curr->time_to_die);
		printf("time to eat = %d\n", curr->time_to_eat);
		printf("time to think = %d\n", curr->time_to_think);
		printf("number of eat = %d\n", curr->number_of_eat);
		printf("forks = %d %d\n", curr->forks[0], curr->forks[1]);
		printf("fork_right = %d\n", curr->fork_right);
		printf("address = %p\n", (void *)curr);
		printf("next = %p\n", (void *)curr->next);
		printf("prev = %p\n", (void *)curr->prev);
		printf("-----------------------------\n");
		curr = curr->next;
		i++;
	}
}
