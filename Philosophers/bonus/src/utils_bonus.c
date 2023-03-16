/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyurtsev <fyurtsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:03:07 by fyurtsev          #+#    #+#             */
/*   Updated: 2022/12/28 13:03:09 by fyurtsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers_bonus.h"

void	print_error_b(char *message)
{
	printf("%s\n", message);
	exit(0);
}

void	act_printer_b(t_philosopher *phil, t_simulation *sim, char *msg)
{
	sem_wait(sim->typing);
	if (!sim->is_dead)
	{
		printf("ms : %lli ", get_ms() - sim->start_time);
		printf("phil : %i %s\n", phil->id, msg);
	}
	sem_post(sim->typing);
}

long long	get_ms(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	i_need_sleep_b(t_simulation *sim, long long time)
{
	long long	this_time;

	this_time = get_ms();
	while (!sim->is_dead)
	{
		if (get_ms() - this_time >= time)
			break ;
		usleep (42);
	}
}

int	ft_atoi(char *nbr)
{
	int	index;
	int	sign;
	int	number;

	sign = 1;
	index = 0;
	number = 0;
	while ((nbr[index] <= 13 && nbr[index] >= 9) || nbr[index] == ' ')
		index++;
	if (nbr[index] == '-')
		sign *= -1;
	else if (nbr[index] == '+')
		index++;
	while (nbr[index] >= '0' && nbr[index] <= '9')
	{
		number *= 10;
		number += (nbr[index] - '0');
		index++;
	}
	return (number * sign);
}
