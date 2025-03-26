/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:58:43 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/26 17:57:25 by miteixei         ###   ########.fr       */
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

bool	gods_will(t_chronos *god);

#endif
