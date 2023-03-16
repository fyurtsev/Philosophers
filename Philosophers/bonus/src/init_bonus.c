/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyurtsev <fyurtsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:02:55 by fyurtsev          #+#    #+#             */
/*   Updated: 2022/12/28 13:02:57 by fyurtsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers_bonus.h"

void	ft_seminit(t_simulation *sim)
{
	sem_unlink("/p_forks");
	sim->forks = sem_open("/p_forks", O_CREAT, S_IRWXG, sim->phil_count);
	if (sim->forks <= 0)
		print_error_b("sem_open hatasi");
}

void	phil_init(t_simulation *sim)
{
	int	i;

	i = sim->phil_count;
	while (--i >= 0)
	{
		sim->philosophers[i].id = i + 1;
		sim->philosophers[i].last_eat = get_ms();
		sim->philosophers[i].i_eat = 0;
		sim->philosophers[i].sim = sim;
	}
}

void	init_all_b(t_simulation *sim, char **argv)
{
	sim->phil_count = ft_atoi(argv[1]);
	sim->die_time = ft_atoi(argv[2]);
	sim->eat_time = ft_atoi(argv[3]);
	sim->sleep_time = ft_atoi(argv[4]);
	sim->is_dead = false;
	sim->all_eatedboii = false;
	sim->start_time = get_ms();
	sim->philosophers = malloc(sizeof(t_philosopher) * sim->phil_count);
	if (argv[5])
		sim->eat_counter = ft_atoi(argv[5]);
	else
		sim->eat_counter = -1;
	ft_seminit(sim);
	phil_init(sim);
}
