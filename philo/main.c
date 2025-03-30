/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 19:19:44 by miteixei          #+#    #+#             */
/*   Updated: 2025/03/30 19:20:19 by miteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (!parse_args(argc, argv + 1, arg_nums))
		return (-1);
	init_god(&god, arg_nums);
	init_philos(&god);
	init_mutexes(&god);
	god.genesis = get_time();
	create_philos(&god);
	monitor_philos(&god);
}
