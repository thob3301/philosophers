/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:17:45 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/30 19:18:57 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	_atoi(char *a)
{
	int	i;

	i = 0;
	while (*a)
		i = (i * 10) + (*(a++) - '0');
	return (i);
}

long int	_atol(char *a)
{
	long int	i;

	i = 0;
	while (*a)
		i = (i * 10) + (*(a++) - '0');
	return (i);
}

// Convert all arguments to long longs and put them in the array
bool	parse_args(int argc, char **argv, int *arg_nums)
{
	while (*argv)
	{
		*arg_nums = _atoi(*argv);
		if (*arg_nums != _atol(*argv))
			return (false);
		++arg_nums;
		++argv;
	}
	if (argc == 5)
		*arg_nums = 0;
	return (true);
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
