/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:10:07 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/30 19:10:40 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// I'm putting the seconds and microseconds into a single long value
long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long int)tv.tv_sec * 1000
		+ (long int)tv.tv_usec / 1000);
}

// To speak, a philosopher will have to lock the speech_mutex then check if
//   God wills them to speak
void	speak(t_philo *philo, enum e_actions line_n)
{
	pthread_mutex_lock(&philo->god->speech_mutex);
	if (gods_will(philo->god))
		printf("%5ld %3d %s\n", get_time() - philo->god->genesis,
			philo->num, philo->god->speech[line_n]);
	pthread_mutex_unlock(&philo->god->speech_mutex);
}

// But sometimes speech comes directly from God after everything ends
void	speak_without_permission(t_philo *philo, enum e_actions line_n)
{
	pthread_mutex_lock(&philo->god->speech_mutex);
	printf("%5ld %3d %s\n", get_time() - philo->god->genesis,
		philo->num, philo->god->speech[line_n]);
	pthread_mutex_unlock(&philo->god->speech_mutex);
}
