/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:33:05 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/13 16:33:06 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int		print_state(t_philosopher *philo, struct timeval tv, char *str)
{
	pthread_mutex_lock(philo->print_mutex);
	if (!*(philo->is_over))
		dprintf(1, "%d %d %s\n", get_relative_time(philo->start, tv), philo->number, str);
	pthread_mutex_unlock(philo->print_mutex);
	return (SUCCESS);
}

int		get_relative_time(struct timeval start, struct timeval tv)
{
	return((tv.tv_sec - start.tv_sec) * 1000 + (tv.tv_usec - start.tv_usec) / 1000);
}

int		get_time_since_start(t_philosopher *philo)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	// check_dead(tv, philo);
	return(get_relative_time(philo->start, tv));
}

int		check_dead(struct timeval tv, t_philosopher *philo)
{
	if (get_relative_time(philo->start, tv) - philo->time_last_meal > philo->t_die)
	{
		pthread_mutex_lock(philo->print_mutex);
		if (!*(philo->is_over))
			printf("%d %d %s\n", get_relative_time(philo->start, tv), philo->number, "died");
		*(philo->is_over) = 1;
		philo->state = DEAD;		
		pthread_mutex_unlock(philo->print_mutex);
	}
	return (SUCCESS);
}
