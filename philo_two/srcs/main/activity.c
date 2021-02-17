/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:36:54 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 08:49:53 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	get_forks(t_philosopher *philo)
{
	struct timeval tv;

	while (philo->number != *philo->next_philo_eat)
		;
	sem_wait(philo->fork_sem);

	gettimeofday(&tv, NULL);
	print_state(philo, tv, "has taken a fork");

	sem_wait(philo->fork_sem);

	*philo->next_philo_eat = (*philo->next_philo_eat % philo->nb_philo) + 1;

	gettimeofday(&tv, NULL);
	print_state(philo, tv, "has taken a fork");
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
		print_state(philo, start_eat, "is_eating");
		philo->time_last_meal = get_relative_time(philo->start, start_eat);
		while (get_relative_time(start_eat, tv) < philo->t_eat &&
				*philo->is_over < philo->nb_philo)
			gettimeofday(&tv, NULL);
	}
	sem_post(philo->fork_sem);
	sem_post(philo->fork_sem);
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

static int		ft_sleep(t_philosopher *philo)
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
