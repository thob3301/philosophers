/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:58:10 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/19 19:37:13 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// I'm putting the seconds and microseconds into a single long long value
unsigned long long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long long int)(tv.tv_sec * 1000)
		+ (unsigned long long int)(tv.tv_usec / 1000));
}

// To speak, a philosopher will have to lock the speech_mutex then check if
//   God wills them to speak
void	speak(t_philo *philo, enum e_actions line_n)
{
	pthread_mutex_lock(&philo->god->speech_mutex);
	if (!abort_y_n(philo->god))
		printf("%lld %d %s\n", get_time() - philo->god->genesis,
			philo->num, philo->god->speech[line_n]);
	pthread_mutex_unlock(&philo->god->speech_mutex);
}

void	free_philos(t_chronos *god)
{
	t_philo	*philo_ptr;
	t_philo	*philo_ptr_destroy;

	philo_ptr = god->first;
	while (1)
	{
		pthread_join(philo_ptr->thread, NULL);
		pthread_mutex_destroy(&philo_ptr->fork_mutex);
		pthread_mutex_destroy(&philo_ptr->time_mutex);
		philo_ptr_destroy = philo_ptr;
		if (philo_ptr->num != god->number_of_philosophers)
			philo_ptr = philo_ptr->next;
		else
			philo_ptr = NULL;
		memset(philo_ptr_destroy, '\0', sizeof(t_philo));
		free(philo_ptr_destroy);
		if (!philo_ptr)
			break ;
	}
}

void	end_creation(t_chronos *god)
{
	pthread_mutex_destroy(&god->speech_mutex);
	pthread_mutex_destroy(&god->abort_mutex);
	memset(god, '\0', sizeof(t_chronos));
}

void	check_death(t_chronos *god)
{
	t_philo	*philo_ptr;

	philo_ptr = god->first;
	while (1)
	{
		pthread_mutex_lock(&philo_ptr->time_mutex);
		if (philo_ptr->time_last_ate + god->time_to_die >= get_time())
		{
			pthread_mutex_lock(&god->abort_mutex);
			god->abort = true;
			pthread_mutex_unlock(&god->abort_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo_ptr->time_mutex);
		philo_ptr = philo_ptr->next;
	}
	free_philos(god);
	end_creation(god);
}

void	think(t_philo *philo)
{
	speak(philo, THINK);
	while (1)
	{
		pthread_mutex_lock(&philo->time_mutex);
		if (philo->time_last_ate + philo->god->time_to_die - 100 <= get_time())
			break ;
		pthread_mutex_unlock(&philo->time_mutex);
		usleep(10000);
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
		usleep(10000);
	}
}

// To eat, even number philosophers need to pick up the right fork first
//   and then the left one
// Odd number philosophers do it the other way around
void	eat2(t_philo *philo)
{
	philo->time_deadline = get_time() + philo->god->time_to_eat;
	pthread_mutex_lock(&philo->time_mutex);
	philo->time_last_ate = get_time();
	pthread_mutex_unlock(&philo->time_mutex);
	speak(philo, EAT);
	while (1)
	{
		if (philo->time_deadline <= get_time())
			break ;
		usleep(10000);
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
	eat2(philo);
}

// The abort condition is guarded by a mutex.
// All the philosophers do is read it, but because the God thread needs to write
//   into it at a moment's notice, the mutex is needed to avoid a race condition
// The philosophers essecially pray to God
//   to decide whether to proceed with their activities
// Let's not think about it too much
bool	abort_y_n(t_chronos *god)
{
	bool	condition;

	pthread_mutex_lock(&god->abort_mutex);
	condition = god->abort;
	pthread_mutex_unlock(&god->abort_mutex);
	return (condition);
}

// Every philosopher loops between eating, sleeping, and thinking
// They don't read books, however, they must have read them all by now
// Before reentering the loop the abort condition is checked,
//   as well as in between actions
void	*philo_main(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	pthread_detach(philo->thread);
	while (!abort_y_n(philo->god))
	{
		eat(philo);
		if (abort_y_n(philo->god))
			break ;
		_sleep(philo);
		if (abort_y_n(philo->god))
			break ;
		think(philo);
	}
	return (NULL);
}

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

long long int	_atol(char *a)
{
	long long int	i;

	i = 0;
	while (*a)
		i += (i * 10) + (*(a++) - '0');
	return (i);
}

// Convert all arguments to long longs and put them in the array
void	parse_args(int argc, char **argv, int *arg_nums)
{
	while (*argv)
		*(arg_nums++) = _atol(*(argv++));
	if (argc == 5)
		*arg_nums = 0;
}

// Check if every character in arguments is a digit
bool	vibe_check(char **argv)
{
	char	*str;

	while (*(++argv))
	{
		str = *argv;
		if (*str == '\0')
			return (false);
		while (*str && ('0' <= *str && *str <= '9'))
			++str;
		if (*str != '\0')
			return (false);
	}
	return (true);
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
	god->genesis = -1;
	god->speech = action;
	pthread_mutex_init(&god->speech_mutex, NULL);
	pthread_mutex_init(&god->abort_mutex, NULL);
	god->abort = false;
}

// Check args,
//   parse args,
//   init god struct,
//   init philos structs,
//   init mutexes,
//   write down start time,
//   spawn threads,
//   check end condition on loop
int	main(int argc, char **argv)
{
	t_chronos	god;
	int			arg_nums[5];

	if ((argc != 5 && argc != 6) || !vibe_check(argv))
		return (-1);
	parse_args(argc, argv + 1, arg_nums);
	init_god(&god, arg_nums);
	init_philos(&god);
	init_mutexes(&god);
	god.genesis = get_time();
	create_philos(&god);
	check_death(&god);
}
