/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:36:54 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 11:20:27 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	get_forks(t_philosopher *philo)
{
	int	time;

	while (philo->number != philo->game->next_philo_eat)
		;
	sem_wait(philo->game->fork_sem);

	time = get_time();
	print_state(philo, time, "has taken a fork");

	sem_wait(philo->game->fork_sem);

	philo->game->next_philo_eat = (philo->game->next_philo_eat % philo->game->nb_philo) + 1;

	time = get_time();
	print_state(philo, time, "has taken a fork");
	return (SUCCESS);
}

static int	ft_eat(t_philosopher *philo, int *count)
{
	int	start_eat;
	int	time;

	start_eat = get_time();
	time = start_eat;
	if (philo->game->is_over < philo->game->nb_philo)
	{
		print_state(philo, start_eat, "is_eating");
		philo->time_last_meal = start_eat;
		while (time - start_eat < philo->game->t_eat &&
				philo->game->is_over < philo->game->nb_philo)
			time = get_time();
	}
	sem_post(philo->game->fork_sem);
	sem_post(philo->game->fork_sem);
	(*count)++;
	if (philo->game->is_over < philo->game->nb_philo &&
		(*count < philo->game->nb_philo_eat || !philo->game->nb_philo_eat))
		print_state(philo, time, "is sleeping");
	if (philo->game->is_over < philo->game->nb_philo && *count == philo->game->nb_philo_eat)
	{
		print_state(philo, time, "is full");
		philo->state = FULL;
		philo->game->is_over++;
	}
	return (SUCCESS);
}

static int		ft_sleep(t_philosopher *philo)
{
	int	start_sleep;
	int	time;

	start_sleep = get_time();
	time = start_sleep;
	if (philo->game->is_over < philo->game->nb_philo)
	{
		while (time - start_sleep < philo->game->t_sleep &&
				philo->game->is_over < philo->game->nb_philo)
			time = get_time();
	}
	if (philo->game->is_over < philo->game->nb_philo)
		print_state(philo, time, "is thinking");
	return (SUCCESS);
}

int		philo_circle(t_philosopher *philo, int *count)
{
	get_forks(philo);
	ft_eat(philo, count);
	if (!philo->game->nb_philo_eat || *count < philo->game->nb_philo_eat)
		ft_sleep(philo);
	return (SUCCESS);
}
