#include "../../includes/philosophers.h"

static int	ft_eat(t_philosopher *philo)
{
	struct timeval	start_eat;
	struct timeval	tv;

	gettimeofday(&start_eat, NULL);	// valeur retour a checker ?
	gettimeofday(&tv, NULL); // valeur retour a checker ?
	while (((tv.tv_sec - start_eat.tv_sec) * 1000 +
			tv.tv_usec - start_eat.tv_usec) < philo->t_sleep)
		gettimeofday(&tv, NULL); // valeur retour a checker ?

	pthread_mutex_unlock(&philo->fork_l->mutex);
	pthread_mutex_unlock(&philo->fork_r->mutex);

	return (SUCCESS);
}

static int	ft_sleep(t_philosopher *philo)
{
	struct timeval	start_sleep;
	struct timeval	tv;

	gettimeofday(&start_sleep, NULL);	// valeur retour a checker ?
	gettimeofday(&tv, NULL); // valeur retour a checker ?
	while (((tv.tv_sec - start_sleep.tv_sec) * 1000 +
			tv.tv_usec - start_sleep.tv_usec) < philo->t_sleep)
	{
		check_dead(philo);
		if (philo->state == DEAD)
			return (SUCCESS);
		gettimeofday(&tv, NULL); // valeur retour a checker ?
	}
	return (SUCCESS);
}

/////////////////////////////////////////////////
int	get_forks(t_philosopher *philo)
{
	while (pthread_mutex_lock(&philo->fork_l->mutex))
	{
		check_dead(philo);
		if (philo->state == DEAD)
			return (DEAD);
	}
	while (pthread_mutex_lock(&philo->fork_r->mutex))
	{
		check_dead(philo);
		if (philo->state == DEAD)
			return (DEAD);
	}
	return (SUCCESS);
}
/////////////////////////////////////////////////


int		philo_eat(t_philosopher *philo, int *count)
{
	// gestion des fork et mutex a ajouter
	if (get_forks(philo) == DEAD)
		return (SUCCESS);

	dprintf(1, "%d %d is eating\n", get_time_since_start(philo), philo->number);	// printf
	ft_eat(philo);
	(*count)++;
	philo->state = SLEEPING;
	return (SUCCESS);
}

int		philo_sleep(t_philosopher *philo)
{
	dprintf(1, "%d %d is sleeping\n", get_time_since_start(philo), philo->number);	// printf
	ft_sleep(philo);
	philo->state = THINKING;
	return (SUCCESS);
}

int		philo_think(t_philosopher *philo)
{
	dprintf(1, "%d %d is thinking\n", get_time_since_start(philo), philo->number);	// printf
	philo->state = EATING;
	return (SUCCESS);
}
