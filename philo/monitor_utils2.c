/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:10:52 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/30 21:28:23 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_hunger(t_philo *philo_ptr, bool *well_fed, long int times_eaten)
{
	bool		all_satiated;
	long int	philo_num;

	all_satiated = false;
	if (times_eaten
		>= philo_ptr->god->number_of_times_each_philosopher_must_eat)
	{
		well_fed[philo_ptr->num - 1] = true;
		all_satiated = true;
		philo_num = philo_ptr->god->number_of_philosophers;
		while (philo_num--)
			all_satiated = all_satiated && *(well_fed++);
	}
	if (all_satiated)
	{
		pthread_mutex_lock(&philo_ptr->god->abort_mutex);
		philo_ptr->god->abort = true;
		pthread_mutex_unlock(&philo_ptr->god->abort_mutex);
	}
	return (all_satiated);
}

void	check_death(t_chronos *god)
{
	t_philo		*philo_ptr;
	long int	last_ate;
	long int	times_eaten;

	philo_ptr = god->first;
	while (1)
	{
		pthread_mutex_lock(&philo_ptr->time_mutex);
		last_ate = philo_ptr->time_last_ate;
		times_eaten = philo_ptr->times_eaten;
		pthread_mutex_unlock(&philo_ptr->time_mutex);
		if (last_ate + god->time_to_die < get_time())
		{
			pthread_mutex_lock(&god->abort_mutex);
			god->abort = true;
			pthread_mutex_unlock(&god->abort_mutex);
			speak_without_permission(philo_ptr, DIE);
			break ;
		}
		if (god->number_of_times_each_philosopher_must_eat
			&& check_hunger(philo_ptr, god->well_fed, times_eaten))
			break ;
		philo_ptr = philo_ptr->next;
		usleep(god->time_to_die * 1000 / god->number_of_philosophers / 50);
	}
}

void	monitor_philos(t_chronos *god)
{
	check_death(god);
	join_philos(god);
	free_philos(god);
	end_creation(god);
}

// The abort condition is guarded by a mutex.
// All the philosophers do is read it, but because the God thread needs to write
//   into it at a moment's notice, the mutex is needed to avoid a race condition
// The philosophers essecially pray to God
//   to decide whether to proceed with their activities
// Let's not think about it too much
bool	gods_will(t_chronos *god)
{
	bool	condition;

	pthread_mutex_lock(&god->abort_mutex);
	condition = !god->abort;
	pthread_mutex_unlock(&god->abort_mutex);
	return (condition);
}
