/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:32:04 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 08:53:17 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	get_one_fork(t_philosopher *philo, t_fork *fork)
{
	struct timeval tv;

	while (philo->number == fork->last_philo)
		;
	pthread_mutex_lock(&fork->mutex);
	fork->last_philo = philo->number;
	gettimeofday(&tv, NULL);
	print_state(philo, tv, "has taken a fork");
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
	struct timeval	start_eat;
	struct timeval	tv;

	gettimeofday(&start_eat, NULL);
	tv = start_eat;
	if (*philo->is_over < philo->nb_philo)
	{
		print_state(philo, start_eat, "is eating");
		philo->time_last_meal = get_relative_time(philo->start, start_eat);
		while (get_relative_time(start_eat, tv) < philo->t_eat &&
				*philo->is_over < philo->nb_philo)
			gettimeofday(&tv, NULL);
	}
	pthread_mutex_unlock(&philo->fork_l->mutex);
	pthread_mutex_unlock(&philo->fork_r->mutex);
	(*count)++;
	if (*philo->is_over < philo->nb_philo &&
		(*count < philo->nb_philo_eat || !philo->nb_philo_eat))
		print_state(philo, tv, "is sleeping");
	if (*philo->is_over < philo->nb_philo && *count == philo->nb_philo_eat)
	{
		print_state(philo, tv, "is full");
		philo->state = FULL;
		(*(philo->is_over))++;
	}
	return (SUCCESS);
}

static int	ft_sleep(t_philosopher *philo)
{
	struct timeval	start_sleep;
	struct timeval	tv;

	gettimeofday(&start_sleep, NULL);
	tv = start_sleep;
	if (*philo->is_over < philo->nb_philo)
	{
		while (get_relative_time(start_sleep, tv) < philo->t_sleep &&
				*philo->is_over < philo->nb_philo)
			gettimeofday(&tv, NULL);
	}
	if (*philo->is_over < philo->nb_philo)
		print_state(philo, tv, "is thinking");
	return (SUCCESS);
}

int		philo_circle(t_philosopher *philo, int *count)
{
	get_forks(philo);
	ft_eat(philo, count);
	if (!philo->nb_philo_eat || *count < philo->nb_philo_eat)
		ft_sleep(philo);
	return (SUCCESS);
}
