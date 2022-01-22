/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:48:41 by dcyprien          #+#    #+#             */
/*   Updated: 2022/01/22 17:43:37 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_them_all(t_philo *philo)
{
	int		i;
	t_philo	*next;

	i = get_num_philo(philo);
	next = philo->next;
	while (i > 1)
	{
		free(philo);
		philo = next;
		next = philo->next;
		i--;
	}
	free(philo);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (0);
	philo = init_philos(av, ft_atoi(av[1]));
	create_threads(philo, get_num_philo(philo));
	// verify_all(philo, ft_atoi(av[1]));
	free_them_all(philo);
	return (1);
}
