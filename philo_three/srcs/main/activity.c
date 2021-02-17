/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:35:06 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 09:08:04 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

static int	get_one_fork(t_philosopher *philo)
{
	struct timeval tv;

	sem_wait(philo->fork_sem);
	gettimeofday(&tv, NULL);
	print_state(philo, tv, "has taken a fork");
	return (SUCCESS);
}

static int	get_forks(t_philosopher *philo)
{
	sem_wait(philo->fork[philo->number - 1]->private_fork_sem);
	get_one_fork(philo);
	get_one_fork(philo);
	sem_post(philo->fork[philo->number % philo->nb_philo]->private_fork_sem);
	return (SUCCESS);
}

static int	ft_eat(t_philosopher *philo, int *count)
{
	struct timeval	start_eat;
	struct timeval	tv;

	gettimeofday(&start_eat, NULL);
	// check_dead(start_eat, philo);
	tv = start_eat;
	print_state(philo, start_eat, "is eating");
	philo->time_last_meal = get_relative_time(philo->start, start_eat);
	while (get_relative_time(start_eat, tv) < philo->t_eat)
	{
		gettimeofday(&tv, NULL);
		// check_dead(tv, philo);
	}
	sem_post(philo->fork_sem);
	sem_post(philo->fork_sem);
	(*count)++;
	if (*count < philo->nb_philo_eat || !philo->nb_philo_eat)
		print_state(philo, tv, "is sleeping");
	if (*count == philo->nb_philo_eat)
	{
		print_state(philo, tv, "is full");
		philo->state = FULL;
	}
	return (SUCCESS);
}

static int	ft_sleep(t_philosopher *philo)
{
	struct timeval	start_sleep;
	struct timeval	tv;

	gettimeofday(&start_sleep, NULL);
	// check_dead(start_sleep, philo);
	tv = start_sleep;
	while (get_relative_time(start_sleep, tv) < philo->t_sleep)
	{
		gettimeofday(&tv, NULL);
		// check_dead(tv, philo);
	}
	print_state(philo, tv, "is thinking");
	
	return (SUCCESS);
}

int philo_circle(t_philosopher *philo, int *count)
{
	get_forks(philo);
	ft_eat(philo, count);
	if (!philo->nb_philo_eat || *count < philo->nb_philo_eat)
		ft_sleep(philo);
	return (SUCCESS);
}
