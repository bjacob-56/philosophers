/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:37:40 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/13 17:48:51 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int		print_state(t_philosopher *philo, struct timeval tv, char *str)
{
	sem_wait(philo->print_sem);

	if (!*(philo->is_over))
		dprintf(1, "%d %d %s\n", get_relative_time(philo->start, tv), philo->number, str);

	sem_post(philo->print_sem);
	
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
		sem_wait(philo->print_sem);
	
		if (!*(philo->is_over))
			printf("%d %d %s\n", get_relative_time(philo->start, tv), philo->number, "died");
		*(philo->is_over) = 1;
		philo->state = DEAD;		

		sem_post(philo->print_sem);
	}
	return (SUCCESS);
}

int		print_errno(void)
{
	dprintf(STDERR_FILENO, "errno: %s\n", strerror(errno));	// dprintf
	return (FAILURE);
}