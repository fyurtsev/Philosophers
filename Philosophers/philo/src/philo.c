/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyurtsev <fyurtsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:04:08 by fyurtsev          #+#    #+#             */
/*   Updated: 2022/12/28 13:04:10 by fyurtsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_maintain(void *args)
{
	unsigned long int	tstamp;
	t_data				*data;
	int					index;

	data = (t_data *) args;
	index = 0;
	while (true)
	{
		if (data->action == data->n_philos)
			break ;
		if (index == data->n_philos)
			index = 0;
		tstamp = get_ms();
		if (!data->philo[index].finished
			&& ((int)(tstamp - data->philo[index].last_eat) > data->tt_die))
		{
			print_action(STR_DEAD, &data->philo[index], tstamp);
			data->running = false;
			break ;
		}
		index++;
	}
	return (NULL);
}

void	*philo_main_loop(void *args)
{
	t_philo	*philo;

	philo = (t_philo *) args;
	philo->last_eat = get_ms();
	philo->data->start = get_ms();
	if (philo->id % 2 == 0)
	{
		pthink(philo);
		usleep(philo->data->tt_eat * 1000);
	}
	while (philo->data->running)
	{
		ptake_forks(philo);
		peat(philo);
		pdrop_forks(philo);
		if (philo->eat_count == philo->data->should_eat)
		{
			philo->finished = true;
			philo->data->action++;
			break ;
		}
		pthink(philo);
		psleep(philo);
	}
	return (NULL);
}
