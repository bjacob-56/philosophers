#include "../../includes/philosophers.h"

int		get_time_since_start(t_philosopher *philo)
{
	struct timeval tv;

	gettimeofday(&tv, NULL); // valeur retour a checker ?
	return((tv.tv_sec - philo->start.tv_sec) * 1000 + tv.tv_usec - philo->start.tv_usec);
}

int		check_dead(t_philosopher *philo)
{
	if (get_time_since_start(philo) - philo->time_last_meal > philo->t_die)
	{
		philo->state = DEAD;
		dprintf(1, "%d %d died\n", get_time_since_start(philo), philo->number);	// printf
	}
	return (SUCCESS);
}
