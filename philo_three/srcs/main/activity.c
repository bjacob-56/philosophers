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

static int	ft_eat(t_philosopher *philo, int *count)
{
	struct timeval	start_eat;
	struct timeval	tv;

	gettimeofday(&start_eat, NULL);	// valeur retour a checker ?
	check_dead(start_eat, philo);
	if (!*(philo->is_over) && philo->state != DEAD)
	{
		// dprintf(1, "%d %d is eating\n", get_relative_time(philo->start, start_eat), philo->number);
		print_state(philo, start_eat, "is_eating");

		philo->time_last_meal = get_relative_time(philo->start, start_eat);
		gettimeofday(&tv, NULL);
		while (get_relative_time(start_eat, tv) < philo->t_eat && philo->state != DEAD)
		{
			gettimeofday(&tv, NULL);
			check_dead(tv, philo);
		}
	}

	// pthread_mutex_unlock(&philo->fork_l->mutex);
	// pthread_mutex_unlock(&philo->fork_r->mutex);
	sem_post(philo->fork_sem);
	sem_post(philo->fork_sem);

	(*count)++;
	if (!*(philo->is_over) && philo->state != DEAD && *count == philo->nb_philo_eat)
		print_state(philo, tv, "is full");
		// dprintf(1, "%d %d is full\n", get_relative_time(philo->start, tv), philo->number); // a garder ?
	return (SUCCESS);
}

/////////////////////////////////////////////////
int	get_forks(t_philosopher *philo)
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


int		philo_eat(t_philosopher *philo, int *count)
{
	get_forks(philo);
	if (philo->state == DEAD)
		return (SUCCESS);
	ft_eat(philo, count);
	philo->state = EATING;
	return (SUCCESS);
}

int		philo_sleep(t_philosopher *philo)
{
	struct timeval	start_sleep;
	struct timeval	tv;

	philo->state = SLEEPING;
	gettimeofday(&start_sleep, NULL);
	check_dead(start_sleep, philo);
	if (!*(philo->is_over) && philo->state != DEAD)
	{
		print_state(philo, start_sleep, "is sleeping");

// dprintf(1, "%d %d is sleeping\n", get_relative_time(philo->start, start_sleep), philo->number);

		gettimeofday(&tv, NULL);
		while (get_relative_time(start_sleep, tv) < philo->t_sleep && philo->state != DEAD)
		{
			gettimeofday(&tv, NULL);
			check_dead(tv, philo);
		}
	}
	return (SUCCESS);
}

int		philo_think(t_philosopher *philo)
{
	struct timeval	start_think;

	philo->state = THINKING;
	gettimeofday(&start_think, NULL);
	check_dead(start_think, philo);
	if (!*(philo->is_over) && philo->state != DEAD)
		print_state(philo, start_think, "is thinking");

// dprintf(1, "%d %d is thinking\n", get_relative_time(philo->start, start_think), philo->number);

	return (SUCCESS);
}
