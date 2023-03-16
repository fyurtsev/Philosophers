/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyurtsev <fyurtsev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 13:02:29 by fyurtsev          #+#    #+#             */
/*   Updated: 2022/12/28 13:05:37 by fyurtsev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>

struct	s_simulation;
typedef struct s_philosopher
{
	int					id;
	int					i_eat;
	long long			last_eat;
	pid_t				p_id;
	pthread_t			dead_check;
	struct s_simulation	*sim;
}		t_philosopher;

typedef struct s_simulation
{
	int				phil_count;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_counter;
	bool			is_dead;
	bool			all_eatedboii;
	long long		start_time;
	sem_t			*typing;
	sem_t			*forks;
	t_philosopher	*philosophers;
}		t_simulation;

void		init_all_b(t_simulation *sim, char **argv);
void		print_error_b(char *message);
int			ft_simulation_b(t_simulation *sim);
long long	get_ms(void);
void		act_printer_b(t_philosopher *phil, t_simulation *sim, char *msg);
void		i_need_sleep_b(t_simulation *sim, long long time);
int			ft_atoi(char *nbr);

#endif