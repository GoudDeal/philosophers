/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:37:39 by dcyprien          #+#    #+#             */
/*   Updated: 2022/01/22 17:43:04 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_values(t_philo **philo, int index, char **av)
{
	(*philo)->thread = 0;
	(*philo)->number = index;
	(*philo)->forks[0] = 0;
	(*philo)->forks[1] = 0;
	(*philo)->time_to_die = ft_atoi(av[2]);
	(*philo)->time_to_eat = ft_atoi(av[3]);
	(*philo)->time_to_think = ft_atoi(av[4]);
	if (av[5])
		(*philo)->number_of_eat = ft_atoi(av[5]);
	else
		(*philo)->number_of_eat = 0;
	(*philo)->mutex = NULL;
	(*philo)->fork_right = 1;
	(*philo)->next = NULL;
	(*philo)->prev = NULL;
}

t_philo	*init_philos(char **av, int num)
{
	t_philo	*new;
	t_philo	*first;
	t_philo	*tmp;
	int		i;

	i = 1;
	first = malloc(sizeof(t_philo));
	set_values(&first, i, av);
	new = first;
	tmp = first;
	i++;
	while (i <= num)
	{
		new->next = malloc(sizeof(t_philo));
		set_values(&new->next, i, av);
		new = new->next;
		new->prev = tmp;
		tmp = new;
		i++;
	}
	new->next = first;
	first->prev = new;
	return (first);
}
