/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:35:06 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 15:12:49 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	get_one_fork(t_philosopher *philo)
{
	int	time;

	sem_wait(philo->game->fork_sem);
	time = get_time();
	print_state(philo, time, "has taken a fork");
	return (SUCCESS);
}

static int	get_forks(t_philosopher *philo)
{
	sem_wait(philo->game->fork[philo->number - 1]->private_fork_sem);
	get_one_fork(philo);
	get_one_fork(philo);
	sem_post(philo->game->fork[philo->number %
			philo->game->nb_philo]->private_fork_sem);
	return (SUCCESS);
}

static int	ft_eat(t_philosopher *philo, int *count)
{
	int	start_eat;
	int	time;

	start_eat = get_time();
	time = start_eat;
	print_state(philo, start_eat, "is eating");
	philo->time_last_meal = start_eat;
	while (time - start_eat < philo->game->t_eat)
		time = get_time();
	sem_post(philo->game->fork_sem);
	sem_post(philo->game->fork_sem);
	(*count)++;
	if (*count < philo->game->nb_philo_eat || !philo->game->nb_philo_eat)
		print_state(philo, time, "is sleeping");
	else if (*count == philo->game->nb_philo_eat)
		print_state(philo, time, "is full");
	return (SUCCESS);
}

static int	ft_sleep(t_philosopher *philo, int *count)
{
	int	start_sleep;
	int	time;

	start_sleep = get_time();
	time = start_sleep;
	if (!philo->game->nb_philo_eat || *count < philo->game->nb_philo_eat)
	{
		while (time - start_sleep < philo->game->t_sleep)
			time = get_time();
		print_state(philo, time, "is thinking");
	}
	return (SUCCESS);
}

int			philo_circle(t_philosopher *philo, int *count)
{
	get_forks(philo);
	ft_eat(philo, count);
	ft_sleep(philo, count);
	return (SUCCESS);
}
