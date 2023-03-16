/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyurtsev <fyurtsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:03:53 by fyurtsev          #+#    #+#             */
/*   Updated: 2022/12/28 13:03:55 by fyurtsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_philo(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->write);
	while (++i < data->n_philos)
		pthread_mutex_destroy(&data->fork[i]);
	free(data->fork);
	free(data->philo);
}
