/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyurtsev <fyurtsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:02:24 by fyurtsev          #+#    #+#             */
/*   Updated: 2022/12/28 13:05:58 by fyurtsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers_bonus.h"

void	eat_bro(t_simulation *sim, t_philosopher *phil)
{
	sem_wait(sim->forks);
	act_printer_b(phil, sim, "has taken a fork");
	sem_wait(sim->forks);
	act_printer_b(phil, sim, "has taken a fork");
	act_printer_b(phil, sim, "eating");
	phil->last_eat = get_ms();
	i_need_sleep_b(sim, sim->eat_time);
	phil->i_eat++;
	sem_post(sim->forks);
	sem_post(sim->forks);
}

void	*thread(void *void_phil)
{
	t_philosopher	*phil;
	t_simulation	*sim;

	phil = (t_philosopher *)void_phil;
	sim = phil->sim;
	while (31 + 11)
	{
		if (get_ms() - phil->last_eat > sim->die_time)
		{
			act_printer_b(phil, sim, "died");
			sim->is_dead = true;
			exit(1);
		}
		if (phil->i_eat >= sim->eat_counter && sim->eat_counter != -1)
			break ;
	}
	return (NULL);
}

void	exit_sim(t_simulation *sim)
{
	int	ret;
	int	i;

	ret = 0;
	i = -1;
	while (++i < sim->phil_count)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < sim->phil_count)
				kill(sim->philosophers[i].p_id, SIGTERM);
		}
	}
	sem_close(sim->forks);
	sem_unlink("./p_forks");
}

void	*p_process(void *void_phil)
{
	t_philosopher	*phil;
	t_simulation	*sim;

	phil = (t_philosopher *)void_phil;
	sim = phil->sim;
	if (phil->id % 2 != 0)
		usleep(sim->eat_time * 1000);
	pthread_create(&phil->dead_check, NULL, thread, void_phil);
	while (!sim->is_dead)
	{
		eat_bro(sim, phil);
		if (sim->eat_counter != -1 && phil->i_eat >= sim->eat_counter)
			break ;
		act_printer_b(phil, sim, "uyuyor");
		i_need_sleep_b(sim, sim->sleep_time);
		act_printer_b(phil, sim, "dusunuyor");
	}
	pthread_join(phil->dead_check, NULL);
	pthread_detach(phil->dead_check);
	exit(0);
}

int	ft_simulation_b(t_simulation *sim)
{
	int				i;
	t_philosopher	*phils;

	phils = sim->philosophers;
	i = -1;
	while (++i < sim->phil_count)
	{
		phils[i].p_id = fork();
		if (phils[i].p_id < 0)
			return (1);
		if (phils[i].p_id == 0)
			p_process(&phils[i]);
	}
	exit_sim(sim);
	return (0);
}
