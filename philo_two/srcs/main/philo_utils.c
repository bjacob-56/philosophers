/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:37:40 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/16 16:16:34 by bjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int		print_state(t_philosopher *philo, struct timeval tv, char *str)
{
	sem_wait(philo->print_sem);

	if (*philo->is_over < philo->nb_philo)
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
	return(get_relative_time(philo->start, tv));
}

int		check_dead(struct timeval tv, t_philosopher *philo)
{
	if (get_relative_time(philo->start, tv) - philo->time_last_meal > philo->t_die)
	{
		sem_wait(philo->print_sem);
		if (*philo->is_over < philo->nb_philo)
			printf("%d %d %s\n", get_relative_time(philo->start, tv), philo->number, "died");
		*(philo->is_over) = philo->nb_philo;
		sem_post(philo->print_sem);
	}
	return (SUCCESS);
}

int		check_all_philo_dead(t_game *game)
{
	int	i;
	struct timeval	tv;

	while (game->is_over < game->nb_philo)
	{
		i = -1;
		while (++i < game->nb_philo && game->is_over < game->nb_philo)
		{
			gettimeofday(&tv, NULL);
			if (!game->nb_philo_eat || ((game->philo)[i])->state != FULL)
				check_dead(tv, (game->philo)[i]);
		}
	}
	return (SUCCESS);
}

int		print_errno(void)	// DEBUG
{
	dprintf(STDERR_FILENO, "errno: %s\n", strerror(errno));	// dprintf
	return (FAILURE);
}
