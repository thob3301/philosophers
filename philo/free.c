/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:13:43 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/30 19:14:12 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_chronos *god)
{
	t_philo	*philo_ptr;
	t_philo	*philo_ptr_destroy;

	philo_ptr = god->first;
	while (1)
	{
		pthread_mutex_destroy(&philo_ptr->fork_mutex);
		pthread_mutex_destroy(&philo_ptr->time_mutex);
		philo_ptr_destroy = philo_ptr;
		if (philo_ptr->num != god->number_of_philosophers)
			philo_ptr = philo_ptr->next;
		else
			philo_ptr = NULL;
		free(philo_ptr_destroy);
		if (!philo_ptr)
			break ;
	}
}

void	join_philos(t_chronos *god)
{
	t_philo	*philo_ptr;

	philo_ptr = god->first;
	while (1)
	{
		pthread_join(philo_ptr->thread, NULL);
		if (philo_ptr->num != god->number_of_philosophers)
			philo_ptr = philo_ptr->next;
		else
			philo_ptr = NULL;
		if (!philo_ptr)
			break ;
	}
}

void	end_creation(t_chronos *god)
{
	pthread_mutex_destroy(&god->speech_mutex);
	pthread_mutex_destroy(&god->abort_mutex);
	free(god->well_fed);
}
