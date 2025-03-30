/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:16:23 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/30 19:19:09 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_well_fed(bool *well_fed, long int n_o_p)
{
	while (n_o_p--)
		*(well_fed++) = false;
}

// Initialize the God struct with the arguments,
//   a couple of mutexes and the abort variable
// The speech_mutex protects stdout and the abort_mutex whether the philo
//   thread should proceed with any action
void	init_god(t_chronos *god, int *arg_nums)
{
	static const char	*action[]
		= {"has taken a fork", "is eating",
		"is sleeping", "is thinking", "died"};

	memset(god, '\0', sizeof(t_chronos));
	god->number_of_philosophers = arg_nums[0];
	god->time_to_die = arg_nums[1];
	god->time_to_eat = arg_nums[2];
	god->time_to_sleep = arg_nums[3];
	god->number_of_times_each_philosopher_must_eat = arg_nums[4];
	god->first = NULL;
	god->genesis = 0;
	god->speech = action;
	pthread_mutex_init(&god->speech_mutex, NULL);
	pthread_mutex_init(&god->abort_mutex, NULL);
	god->abort = false;
	god->well_fed = malloc(god->number_of_philosophers * sizeof(bool));
	init_well_fed(god->well_fed, god->number_of_philosophers);
}
