/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:35:06 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/13 16:35:09 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

/////////////////////////////////////////////////
static int	get_forks(t_philosopher *philo)
{
	struct timeval tv;

// pthread_mutex_lock(philo->fork_mutex);
	// pthread_mutex_lock(&philo->fork_r->mutex);

	sem_wait(philo->place_sem);

	sem_wait(philo->fork_sem);

	gettimeofday(&tv, NULL);
	print_state(philo, tv, "has taken a fork right");
// dprintf(1, "fork = %d\n", philo->fork_l->number);

	// pthread_mutex_lock(&philo->fork_l->mutex);
	sem_wait(philo->fork_sem);

	sem_post(philo->place_sem);

	gettimeofday(&tv, NULL);
	print_state(philo, tv, "has taken a fork left");
// pthread_mutex_unlock(philo->fork_mutex);
	return (SUCCESS);
}
/////////////////////////////////////////////////

static int	ft_eat(t_philosopher *philo, int *count)
{
	struct timeval	start_eat;
	struct timeval	tv;

	gettimeofday(&start_eat, NULL);
	// check_dead(start_eat, philo);
	// gettimeofday(&tv, NULL);
	tv = start_eat;
	if (*philo->is_over < philo->nb_philo)
	{
		print_state(philo, start_eat, "is eating");
		philo->time_last_meal = get_relative_time(philo->start, start_eat);
		while (get_relative_time(start_eat, tv) < philo->t_eat && *philo->is_over < philo->nb_philo)
		{
			gettimeofday(&tv, NULL);
			// check_dead(tv, philo);
		}
	}
	sem_post(philo->fork_sem);
	sem_post(philo->fork_sem);
	(*count)++;
	if (*philo->is_over < philo->nb_philo && *count < philo->nb_philo_eat)
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
	// check_dead(start_sleep, philo);
	// gettimeofday(&tv, NULL);
	tv = start_sleep;
	if (*philo->is_over < philo->nb_philo)
	{
		print_state(philo, start_sleep, "is sleeping");
		while (get_relative_time(start_sleep, tv) < philo->t_sleep && *philo->is_over < philo->nb_philo)
		{
			gettimeofday(&tv, NULL);
			// check_dead(tv, philo);
		}
	}
	// check_dead(tv, philo);
	if (*philo->is_over < philo->nb_philo)
		print_state(philo, tv, "is thinking");
	return (SUCCESS);
}

int philo_circle(t_philosopher *philo, int *count)
{
	get_forks(philo);
	// if (*philo->is_over < philo->nb_philo)
	// 	return (SUCCESS);
	ft_eat(philo, count);
	if (!philo->nb_philo_eat || *count < philo->nb_philo_eat)
		ft_sleep(philo);
	return (SUCCESS);
}
