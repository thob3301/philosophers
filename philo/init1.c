/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:15:09 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/30 19:16:05 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Create each thread
// Every thread is created by God (the main thread),
//   and starts running their code independently
void	create_philos(t_chronos *god)
{
	t_philo	*philo_ptr;

	philo_ptr = god->first;
	while (1)
	{
		philo_ptr->time_last_ate = god->genesis;
		philo_ptr->time_deadline = god->genesis + god->time_to_die;
		pthread_create(&philo_ptr->thread, NULL, &philo_main, philo_ptr);
		if (god->number_of_philosophers == philo_ptr->num)
			break ;
		philo_ptr = philo_ptr->next;
	}
}

// Initialize each philosopher thread's mutexes
void	init_mutexes(t_chronos *god)
{
	t_philo	*philo_ptr;

	philo_ptr = god->first;
	while (1)
	{
		pthread_mutex_init(&philo_ptr->fork_mutex, NULL);
		pthread_mutex_init(&philo_ptr->time_mutex, NULL);
		if (philo_ptr->num == god->number_of_philosophers)
			break ;
		philo_ptr = philo_ptr->next;
	}
}

t_philo	*init_philo(t_chronos *god, int num)
{
	t_philo	*philo_ptr;

	philo_ptr = malloc(sizeof(t_philo));
	memset(philo_ptr, '\0', sizeof(t_philo));
	philo_ptr->num = num;
	philo_ptr->god = god;
	return (philo_ptr);
}

// Generate a struct for each thread and put them into a circular list
void	init_philos(t_chronos *god)
{
	int		philo_i;
	t_philo	*philo_ptr;

	philo_i = 1;
	god->first = init_philo(god, philo_i);
	philo_ptr = god->first;
	while (++philo_i <= god->number_of_philosophers)
	{
		philo_ptr->next = init_philo(god, philo_i);
		philo_ptr = philo_ptr->next;
	}
	philo_ptr->next = god->first;
}
