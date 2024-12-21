/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:58:43 by miteixei          #+#    #+#             */
/*   Updated: 2024/11/27 21:26:07 by miteixei         ###   ########.fr       */
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
	int					time;
	pthread_mutex_t		time_mutex;
	int					time_last_ate;
	int					time_deadline;
	struct s_chronos	*god;
	struct s_philo		*next;
}	t_philo;

typedef struct s_chronos
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	struct s_philo	*first;
	long long int	genesis;
	const char		**speech;
	pthread_mutex_t	speech_mutex;
	pthread_mutex_t	abort_mutex;
	bool			abort;
}	t_chronos;

bool	abort_y_n(t_chronos *god);

#endif
