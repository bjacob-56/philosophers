/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:35:47 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 08:57:46 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int		print_state(t_philosopher *philo, struct timeval tv, char *str)
{
	sem_wait(philo->print_sem);
	dprintf(1, "%d %d %s\n", get_relative_time(philo->start, tv), philo->number, str);
	sem_post(philo->print_sem);
	return (SUCCESS);
}

int		get_relative_time(struct timeval start, struct timeval tv)
{
	return((tv.tv_sec - start.tv_sec) * 1000 + (tv.tv_usec - start.tv_usec) / 1000);
}

int		check_dead(struct timeval tv, t_philosopher *philo)
{
	if (get_relative_time(philo->start, tv) - philo->time_last_meal > philo->t_die)
	{
		sem_wait(philo->print_sem);
		printf("%d %d %s\n", get_relative_time(philo->start, tv), philo->number, "died");
		exit(DEAD);
		// sem_post(philo->print_sem);
	}
	return (SUCCESS);
}

void	*check_dead_philo_background(void *ptr)
{
	t_philosopher *philo;
	struct timeval tv;

	philo = (t_philosopher*)ptr;
	while (1)
	{
		gettimeofday(&tv, NULL);
		check_dead(tv, philo);
	}
	return (ptr);
}
