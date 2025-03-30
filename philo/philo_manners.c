/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manners.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 20:42:13 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/30 20:47:15 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	left_handed(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_mutex);
	speak(philo, FORK);
	pthread_mutex_lock(&philo->next->fork_mutex);
	speak(philo, FORK);
}

void	right_handed(t_philo *philo)
{
	pthread_mutex_lock(&philo->next->fork_mutex);
	speak(philo, FORK);
	pthread_mutex_lock(&philo->fork_mutex);
	speak(philo, FORK);
}
