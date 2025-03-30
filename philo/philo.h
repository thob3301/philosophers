/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:58:43 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/30 20:49:07 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

enum e_actions
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
};

typedef struct s_philo
{
	int					num;
	pthread_t			thread;
	pthread_mutex_t		fork_mutex;
	pthread_mutex_t		time_mutex;
	long int			time_last_ate;
	long int			time_deadline;
	long int			times_eaten;
	struct s_chronos	*god;
	struct s_philo		*next;
}	t_philo;

typedef struct s_chronos
{
	long int		number_of_philosophers;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		number_of_times_each_philosopher_must_eat;
	struct s_philo	*first;
	long int		genesis;
	const char		**speech;
	pthread_mutex_t	speech_mutex;
	pthread_mutex_t	abort_mutex;
	bool			abort;
	bool			*well_fed;
}	t_chronos;

// monitor_utils1.c
long int	get_time(void);
void		speak(t_philo *philo, enum e_actions line_n);
void		speak_without_permission(t_philo *philo, enum e_actions line_n);
// monitor_utils2.c
bool		check_hunger(t_philo *philo_ptr,
				bool *well_fed, long int times_eaten);
void		check_death(t_chronos *god);
void		monitor_philos(t_chronos *god);
bool		gods_will(t_chronos *god);

// free.c
void		free_philos(t_chronos *god);
void		join_philos(t_chronos *god);
void		end_creation(t_chronos *god);

// philo.c
void		think(t_philo *philo);
void		_sleep(t_philo *philo);
void		eat2(t_philo *philo);
void		eat(t_philo *philo);
void		*philo_main(void *ptr);

// philo_manners.c
void		left_handed(t_philo *philo);
void		right_handed(t_philo *philo);

// init1.c
void		create_philos(t_chronos *god);
void		init_mutexes(t_chronos *god);
t_philo		*init_philo(t_chronos *god, int num);
void		init_philos(t_chronos *god);
// init2.c
void		init_well_fed(bool *well_fed, long int n_o_p);
void		init_god(t_chronos *god, int *arg_nums);

// input.c
int			_atoi(char *a);
long int	_atol(char *a);
bool		parse_args(int argc, char **argv, int *arg_nums);
bool		vibe_check(char **argv);

#endif
