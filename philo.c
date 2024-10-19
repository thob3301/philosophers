#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	pthread_t			philo;
	pthread_mutex_t		fork;
	struct s_chronos	*god;
	struct s_philo		*next;
}	t_philo;

typedef struct s_chronos
{
	struct s_philo	*first;
	long long int	time;
	int				*params;
	bool			abort;
}	t_chronos;

void	philo_main(t_chronos *god)
{
	(void)god;
}

t_philo	*init_philo(t_chronos *god)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo.philo = 0;
	philo.fork = 0;
	philo->god = god;
	philo->next = NULL;
	return (philo);
}

t_chronos	*init_god(int **arg_nums)
{
	t_chronos	*god;

	god = malloc(sizeof(t_chronos));
	if (!god)
		return (NULL);
	god->first = NULL;
	god->time = 0;
	god->params = *arg_nums;
	god->abort = false;
}

int	_atoi(char *a)
{
	int	i;

	i = 0;
	while (*a)
		i += i * 10 + (*(a++) - '0');
	return (i);
}

void	parse_args(int argc, char **argv, int **arg_nums)
{
	while (++(*argv))
		*((*arg_nums)++) = _atoi(*argv);
	if (argc == 5)
		**arg_nums = 0;
}

bool	vibe_check(char **argv)
{
	while (++(*argv))
	{
		while ('0' <= **argv && **argv <= '9')
			**argv++;
		if (**argv != '\0')
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_chronos	god;
	int			arg_nums[5];

	if ((argc != 5 && argc != 6) || !vibe_check(argv))
		return (-1);
	parse_args(argc, argv, arg_nums);
	if (!init_god(arg_nums))
		return (-1);
}
