/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyurtsev <fyurtsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:04:03 by fyurtsev          #+#    #+#             */
/*   Updated: 2022/12/28 13:04:05 by fyurtsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_args(argc, argv) == ERROR)
		philo_error("\"CHECK_ARGS(ARGC, ARGV)\" RETURNED_ERROR", ARGS_ERROR);
	else
	{
		start_philo(argc, argv, &data);
		end_philo(&data);
		return (0);
	}
	return (-1);
}
