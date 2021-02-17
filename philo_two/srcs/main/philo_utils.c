/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:37:40 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 15:52:19 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	print_state_full(t_philosopher *philo)
{
	print_state(philo, "is full");
	philo->state = FULL;
	philo->game->is_over++;
	return (SUCCESS);
}

int	print_state(t_philosopher *philo, char *str)
{
	sem_wait(philo->game->print_sem);
	if (philo->game->is_over < philo->game->nb_philo)
	{
		printf("%d %d %s\n", get_time() - philo->game->start_time,
				philo->number, str);
	}
	sem_post(philo->game->print_sem);
	return (SUCCESS);
}

int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_dead(int time, t_philosopher *philo)
{
	if (time - philo->time_last_meal > philo->game->t_die)
	{
		printf("%d %d %s\n", get_time() - philo->game->start_time,
				philo->number, "died");
		philo->game->is_over = philo->game->nb_philo;
	}
	return (SUCCESS);
}

int	check_all_philo_dead(t_game *game)
{
	int	i;

	while (game->is_over < game->nb_philo)
	{
		i = -1;
		while (++i < game->nb_philo && game->is_over < game->nb_philo)
		{
			sem_wait(game->print_sem);
			if (!game->nb_philo_eat || ((game->philo)[i])->state != FULL)
				check_dead(get_time(), (game->philo)[i]);
			sem_post(game->print_sem);
		}
		usleep(100);
	}
	return (SUCCESS);
}
