/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:32:04 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 11:58:11 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	get_one_fork(t_philosopher *philo, t_fork *fork)
{
	int	time;

	while (philo->number == fork->last_philo)
		;
	pthread_mutex_lock(&fork->mutex);
	fork->last_philo = philo->number;
	time = get_time();
	print_state(philo, time, "has taken a fork");
	return (SUCCESS);
}

static int	get_forks(t_philosopher *philo)
{
	if (philo->number % 2)
	{
		get_one_fork(philo, philo->fork_r);
		get_one_fork(philo, philo->fork_l);
	}
	else
	{
		get_one_fork(philo, philo->fork_l);
		get_one_fork(philo, philo->fork_r);
	}
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
		print_state(philo, start_eat, "is eating");
		philo->time_last_meal = start_eat;
		while (time - start_eat < philo->game->t_eat &&
				philo->game->is_over < philo->game->nb_philo)
			time = get_time();
	}
	pthread_mutex_unlock(&philo->fork_l->mutex);
	pthread_mutex_unlock(&philo->fork_r->mutex);
	(*count)++;
	if (philo->game->is_over < philo->game->nb_philo &&
		(*count < philo->game->nb_philo_eat || !philo->game->nb_philo_eat))
		print_state(philo, time, "is sleeping");
	if (philo->game->is_over < philo->game->nb_philo &&
		*count == philo->game->nb_philo_eat)
		print_state_full(philo, time);
	return (SUCCESS);
}

static int	ft_sleep(t_philosopher *philo)
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

int			philo_circle(t_philosopher *philo, int *count)
{
	get_forks(philo);
	ft_eat(philo, count);
	if (!philo->game->nb_philo_eat || *count < philo->game->nb_philo_eat)
		ft_sleep(philo);
	return (SUCCESS);
}
