/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:49:00 by dcyprien          #+#    #+#             */
/*   Updated: 2022/01/22 17:41:47 by dcyprien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo {
	pthread_t			thread;
	pthread_mutex_t		*mutex;
	int					number;
	int					forks[2];
	int					fork_right;
	int					time_to_eat;
	int					time_to_think;
	int					time_to_die;
	int					number_of_eat;
	struct s_philo		*next;
	struct s_philo		*prev;
}				t_philo;

int		ft_atoi(const char *str);
t_philo	*init_philos(char **av, int num);
void	set_values(t_philo **philo, int index, char **av);
void	verify_all(t_philo *philo, int num);
int		ft_isdigit(int c);
int		get_num_philo(t_philo *philo);
void	free_them_all(t_philo *philo);
void	create_threads(t_philo *philo, int num);

#endif