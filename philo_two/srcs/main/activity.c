/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:36:54 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/13 17:49:11 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"


/////////////////////////////////////////////////
static int	get_forks(t_philosopher *philo)
{
	struct timeval tv;

	sem_wait(philo->place_sem);
	sem_wait(philo->fork_sem);

	gettimeofday(&tv, NULL);
	print_state(philo, tv, "has taken a fork right");

	sem_wait(philo->fork_sem);

	sem_post(philo->place_sem);

	gettimeofday(&tv, NULL);
	print_state(philo, tv, "has taken a fork left");
	return (SUCCESS);
}
/////////////////////////////////////////////////

static int	ft_eat(t_philosopher *philo, int *count)
{
	struct timeval	start_eat;
	struct timeval	tv;

	gettimeofday(&start_eat, NULL);
	// check_dead(start_eat, philo);
	gettimeofday(&tv, NULL);
	if (*philo->is_over < philo->nb_philo)
	{
		print_state(philo, start_eat, "is_eating");
		philo->time_last_meal = get_relative_time(philo->start, start_eat);
		while (get_relative_time(start_eat, tv) < philo->t_eat && *philo->is_over < philo->nb_philo)
		{
			gettimeofday(&tv, NULL);
			// check_dead(tv, philo);
		}
	}
	(*count)++;
	if (*philo->is_over < philo->nb_philo && *count < philo->nb_philo_eat)
		print_state(philo, tv, "is sleeping");
	if (*philo->is_over < philo->nb_philo && *count == philo->nb_philo_eat)
		print_state(philo, tv, "is full");
	sem_post(philo->fork_sem);
	sem_post(philo->fork_sem);
	return (SUCCESS);
}

static int		ft_sleep(t_philosopher *philo)
{
	struct timeval	start_sleep;
	struct timeval	tv;

	philo->state = SLEEPING;
	gettimeofday(&start_sleep, NULL);
	// check_dead(start_sleep, philo);
	gettimeofday(&tv, NULL);
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

int		philo_circle(t_philosopher *philo, int *count)
{
	get_forks(philo);
	if (philo->state == DEAD)
		return (SUCCESS);
	ft_eat(philo, count);
	if (*count < philo->nb_philo_eat)
		ft_sleep(philo);
	return (SUCCESS);
}
