/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:58:10 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/30 19:20:17 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo)
{
	long int	_deadline;

	pthread_mutex_lock(&philo->time_mutex);
	_deadline = philo->time_last_ate;
	pthread_mutex_unlock(&philo->time_mutex);
	_deadline += philo->god->time_to_die;
	speak(philo, THINK);
	while (1)
	{
		if (_deadline <= get_time())
			break ;
		usleep(50);
	}
}

void	_sleep(t_philo *philo)
{
	philo->time_deadline = get_time() + philo->god->time_to_sleep;
	speak(philo, SLEEP);
	while (1)
	{
		if (philo->time_deadline <= get_time())
			break ;
		usleep(50);
	}
}

// To eat, even number philosophers need to pick up the right fork first
//   and then the left one
// Odd number philosophers do it the other way around
void	eat2(t_philo *philo)
{
	if (!gods_will(philo->god))
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(&philo->next->fork_mutex);
		return ;
	}
	philo->time_deadline = get_time() + philo->god->time_to_eat;
	pthread_mutex_lock(&philo->time_mutex);
	philo->time_last_ate = get_time();
	if (philo->god->number_of_times_each_philosopher_must_eat)
		++philo->times_eaten;
	pthread_mutex_unlock(&philo->time_mutex);
	while (1)
	{
		if (philo->time_deadline <= get_time())
			break ;
		usleep(50);
	}
	pthread_mutex_unlock(&philo->fork_mutex);
	pthread_mutex_unlock(&philo->next->fork_mutex);
}

void	eat(t_philo *philo)
{
	if (philo->num % 2)
	{
		pthread_mutex_lock(&philo->fork_mutex);
		speak(philo, FORK);
		pthread_mutex_lock(&philo->next->fork_mutex);
		speak(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->next->fork_mutex);
		speak(philo, FORK);
		pthread_mutex_lock(&philo->fork_mutex);
		speak(philo, FORK);
	}
	philo->time_deadline = get_time() + philo->god->time_to_eat;
	speak(philo, EAT);
	eat2(philo);
}

// Every philosopher loops between eating, sleeping, and thinking
// They don't read books, however, they must have read them all by now
// Before reentering the loop the abort condition is checked,
//   as well as in between actions
void	*philo_main(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->num == philo->next->num)
	{
		pthread_mutex_lock(&philo->god->speech_mutex);
		printf("Existence is futile\n");
		pthread_mutex_unlock(&philo->god->speech_mutex);
		return (NULL);
	}
	while (1)
	{
		if (!gods_will(philo->god))
			break ;
		eat(philo);
		if (!gods_will(philo->god))
			break ;
		_sleep(philo);
		if (!gods_will(philo->god))
			break ;
		think(philo);
	}
	return (NULL);
}
