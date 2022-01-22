/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:42:38 by dcyprien          #+#    #+#             */
/*   Updated: 2022/01/22 15:43:56 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	get_num_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo->number > i)
	{
		i = philo->number;
		philo = philo->next;
	}
	return (i);
}
