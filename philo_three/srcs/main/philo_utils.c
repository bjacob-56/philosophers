/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:35:47 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/18 08:35:24 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int		print_state(t_philosopher *philo, char *str)
{
	sem_wait(philo->game->print_sem);
	printf("%d %d %s\n", get_time() - philo->game->start_time,
			philo->number, str);
	sem_post(philo->game->print_sem);
	return (SUCCESS);
}

int		get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	inc_sem_end(t_game *game)
{
	int i;

	i = -1;
	while (++i < game->nb_philo)
		sem_post(game->end_sem);
	sem_wait(game->print_sem);
}

int		check_dead(int time, t_philosopher *philo)
{
	if (time - philo->time_last_meal > philo->game->t_die)
	{
		printf("%d %d %s\n", get_time() - philo->game->start_time,
				philo->number, "died");
		inc_sem_end(philo->game);
	}
	return (SUCCESS);
}

void	*check_dead_philo_background(void *ptr)
{
	t_philosopher *philo;

	philo = (t_philosopher*)ptr;
	while (1)
	{
		sem_wait(philo->game->print_sem);
		check_dead(get_time(), philo);
		sem_post(philo->game->print_sem);
		usleep(100);
	}
	return (ptr);
}
