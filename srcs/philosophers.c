/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:48:41 by dcyprien          #+#    #+#             */
/*   Updated: 2022/02/16 20:55:35 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_max_int(char *av)
{
	int		num;
	char	*str;
	int		i;

	i = 0;
	num = ft_atoi(av);
	str = ft_itoa(num);
	while (av[i] && str[i])
	{
		if (av[i] != str[i])
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_arg(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = 0;
		if (check_max_int(av[i]) == EXIT_FAILURE)
			return (EXIT_MAX_INT);
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 1)
				j++;
			else
				return (EXIT_FAILURE);
		}
	}
	if (i < 5 || i > 6)
	{
		printf("Usage : ./philo nmbr_of_philo time_to_die time_to_eat time_to_sleep [number of meals]\n");
		return (EXIT_FAILURE);
	}
	if (ft_atoi(av[1]) == 0)
		return (NO_PHILO);
	if (ft_atoi(av[1]) == 1)
		return (ONE_PHILO);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_philo		*philo;
	t_status	*tmp;

	tmp = NULL;
	(void)ac;
	if (check_arg(av) == EXIT_FAILURE)
		return (0);
	if (check_arg(av) == NO_PHILO)
		return (1);
	if (check_arg(av) == EXIT_MAX_INT)
	{
		// printf("")
	}
	if (check_arg(av) == ONE_PHILO)
	{
		printf("%s0 %s1 %shas taken a fork%s\n", BLUE, RED, WHITE, RESET);
		usleep(ft_atoi(av[2]) * 1000);
		printf("%s%d %s1 %sdied%s\n", BLUE, ft_atoi(av[2]), RED, WHITE, RESET);
		return (1);
	}
	philo = init_philos(av, ft_atoi(av[1]) - 1, &tmp);
	create_threads(philo, ft_atoi(av[1]));
	free(tmp->starting_time);
	free(tmp);
	free_the_mutex(philo);
	free_them_all(philo);
	return (1);
}
