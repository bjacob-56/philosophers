#include "../../includes/philosophers.h"

int		get_relative_time(struct timeval start, struct timeval tv)
{
	return((tv.tv_sec - start.tv_sec) * 1000 + (tv.tv_usec - start.tv_usec) / 1000);
}

int		get_time_since_start(t_philosopher *philo)
{
	struct timeval tv;

	gettimeofday(&tv, NULL); // valeur retour a checker ?
	// check_dead(tv, philo);
	return(get_relative_time(philo->start, tv));
}

int		check_dead(struct timeval tv, t_philosopher *philo)
{
	if (get_relative_time(philo->start, tv) - philo->time_last_meal > philo->t_die)
	{
		philo->state = DEAD;
		dprintf(1, "%d %d died\n", get_time_since_start(philo), philo->number);	// printf
	}
	return (SUCCESS);
}
