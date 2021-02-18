/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:32:04 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/18 10:09:23 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	get_one_fork(t_philosopher *philo, t_fork *fork)
{
	int	time;

	while (philo->game->is_over < philo->game->nb_philo &&
		philo->number == fork->last_philo)
		;
	pthread_mutex_lock(&fork->mutex);
	fork->last_philo = philo->number;
	time = get_time();
	print_state(philo, "has taken a fork");
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
		philo->time_last_meal = start_eat;
		print_state(philo, "is eating");
		while (time - start_eat < philo->game->t_eat &&
				philo->game->is_over < philo->game->nb_philo)
			time = get_time();
	}
	pthread_mutex_unlock(&philo->fork_l->mutex);
	pthread_mutex_unlock(&philo->fork_r->mutex);
	(*count)++;
	if (philo->game->is_over == philo->game->nb_philo - 1 &&
		*count == philo->game->nb_philo_eat)
		print_state_full(philo);
	if (philo->game->is_over < philo->game->nb_philo &&
		*count == philo->game->nb_philo_eat)
		philo->game->is_over++;
	return (SUCCESS);
}

static int	ft_sleep(t_philosopher *philo)
{
	int	start_sleep;
	int	time;

	if (philo->game->is_over < philo->game->nb_philo)
		print_state(philo, "is sleeping");
	start_sleep = get_time();
	time = start_sleep;
	if (philo->game->is_over < philo->game->nb_philo)
	{
		while (time - start_sleep < philo->game->t_sleep &&
				philo->game->is_over < philo->game->nb_philo)
			time = get_time();
	}
	if (philo->game->is_over < philo->game->nb_philo)
		print_state(philo, "is thinking");
	return (SUCCESS);
}

int			philo_circle(t_philosopher *philo, int *count)
{
	get_forks(philo);
	ft_eat(philo, count);
	ft_sleep(philo);
	return (SUCCESS);
}
