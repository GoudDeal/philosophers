/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:49:00 by dcyprien          #+#    #+#             */
/*   Updated: 2022/02/21 15:11:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define BLACK "\e[0;30m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define MAGENTA "\e[0;35m"
# define CYAN "\e[0;36m"
# define WHITE "\e[0;37m"
# define RESET "\e[0m"
# define ONE_PHILO 2
# define NO_PHILO 3
# define EXIT_MAX_INT 4

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>

enum e_action {
	THINK,
	SLEEP,
	EAT,
	DIE
};

typedef struct s_status {
	struct timeval	*starting_time;
	int				all_started;
	int				all_alive;
}				t_status;

typedef struct s_philo {
	pthread_t			thread;
	pthread_mutex_t		*var;
	pthread_mutex_t		*dead;
	pthread_mutex_t		*time_lock;
	pthread_mutex_t		*fork;
	pthread_mutex_t		*prev_fork;
	pthread_mutex_t		*lock_output;
	struct timeval		*time_last_meal;
	t_status			status;
	int					number;
	int					action;
	int					done;
	long int			time_to_eat;
	long int			time_to_sleep;
	long int			time_to_die;
	int					number_of_eat;
	struct s_philo		*next;
	struct s_philo		*prev;
}				t_philo;

int			ft_atoi(const char *str);
t_philo		*init_philos(char **av, int num, t_status **tmp);
void		set_values(t_philo **philo, int index, char **av);
void		verify_all(t_philo *philo, int num);
int			ft_isdigit(int c);
int			get_num_philo(t_philo *philo);
void		free_them_all(t_philo *philo);
void		create_threads(t_philo *philo, int num);
t_status	*init_status(void);
void		philo_does(t_philo *philo);
void		philo_eats(t_philo *philo);
int	verify_alive(t_philo *philo);
void		exit_philo(t_philo *philo);
void		philo_sleep(t_philo *philo);
long		time_passed(struct timeval ref, int compare);
void		philo_thinks(t_philo *philo);
void		sleeps(t_philo *philo, int time);
void		free_the_mutex(t_philo *philo);
void		unlock_the_mutex(t_philo *philo);
void		philo_dies(t_philo *philo);
int			check_all_alive(t_philo *philo);
void		update_action(t_philo *philo, int action);
void		set_all_dead(t_philo *philo);
void		set_all_done(t_philo *philo);
void		write_done(t_philo *philo);
void		philo_output(t_philo *philo, char *msg);
void		wait_forks(t_philo *philo);
void		print_forks(t_philo *philo);
void		philo_takes_forks(t_philo *philo);
void		lock_fork_even(t_philo *philo);
void		lock_fork_odd(t_philo *philo);
char	*ft_itoa(int n);
void	philo_takes_forks_odd(t_philo *philo);
#endif