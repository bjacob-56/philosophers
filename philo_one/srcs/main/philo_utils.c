/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:33:05 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/18 13:41:40 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	print_state_full(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->game->print_mutex);
	if (philo->game->is_over == philo->game->nb_philo - 1)
	{
		printf("%d Every philosopher has eaten %d times\n",
				get_time() - philo->game->start_time,
				philo->game->nb_philo_eat);
	}
	philo->game->is_over++;
	pthread_mutex_unlock(&philo->game->print_mutex);
	return (SUCCESS);
}

int	print_state(t_philosopher *philo, char *str)
{
	pthread_mutex_lock(&philo->game->print_mutex);
	if (philo->game->is_over < philo->game->nb_philo)
	{
		printf("%d %d %s\n", get_time() - philo->game->start_time,
				philo->number, str);
	}
	pthread_mutex_unlock(&philo->game->print_mutex);
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
	if (time - philo->time_last_meal >= philo->game->t_die)
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
			pthread_mutex_lock(&game->print_mutex);
			check_dead(get_time(), (game->philo)[i]);
			pthread_mutex_unlock(&game->print_mutex);
		}
		usleep(100);
	}
	return (SUCCESS);
}
