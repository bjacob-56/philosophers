#include "../../includes/philosophers.h"

int		check_dead(t_philosopher *philo, struct timeval *start)
{
	if (get_time_since_start(start) - philo->time_last_meal > philo->t_die)
	{
		philo->state = DEAD;
		printf("%d %d died\n", get_time_since_start(start), philo->number);	// printf
	}
	return (SUCCESS);
}

int		ft_sleep(t_philosopher *philo, struct timeval *start)
{
	struct timeval	*start;
	struct timeval	*tv;

	gettimeofday(start, NULL);	// valeur retour a checker ?
	gettimeofday(tv, NULL); // valeur retour a checker ?
	while (tv->tv_sec - start->tv_sec) * 1000 +
			tv->tv_usec - start->tv_usec < philo->t_sleep)
	{
		check_dead(philo, start);
		if (philo->state == DEAD)
			return (SUCCESS);
		gettimeofday(tv, NULL); // valeur retour a checker ?
	}
	return (SUCCESS);
}

int		philo_eat(t_philosopher *philo, struct timeval *start)
{
	// A FAIRE
}

int		philo_think(t_philosopher *philo, struct timeval *start)
{
	ft_sleep(philo->t_sleep);
	philo->state = SLEEPING;
	return (SUCCESS);
}

int		philo_sleep(t_philosopher *philo, struct timeval *start)
{
	printf("%d %d is sleeping\n", get_time_since_start(start), philo->number);	// printf
	ft_sleep(philo);
	philo->state = THINKING;
	return (SUCCESS);
}

int		get_time_since_start(struct timeval *start)
{
	struct timeval *tv;

	gettimeofday(tv, NULL); // valeur retour a checker ?
	return((tv->tv_sec - start->tv_sec) * 1000 + tv->tv_usec - start->tv_usec);
}

void	*launch_philo(t_philosopher *philo)
{
	int				count;
	int				time;
	struct timeval	*start;


	gettimeofday(start, NULL);	// valeur retour a checker ?

	count = 0;
	while (philo->state != DEAD &&
		(!philo->nb_philo_eat || count < philo->nb_philo_eat))
	{
		check_dead(philo, start);
		if (philo->state == THINKING)
			philo_eat(philo);
		if (philo->state == EATING)
			philo_sleep(philo, start);
		if (philo->state == SLEEPING)
			philo_think(philo);
		// pthread_mutex_unlock(mutex);
	}
	return (NULL);	// quelle valeur ?
}

int	create_thread_philo(t_game *game, int i)
{
	pthread_t thread;

	if (pthread_create(&thread, NULL, &launch_philo, (game->philo)[i]))
		return (ft_error(game, NULL, F_THREAD_CREATE))
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;
	
	if (catch_arg(game, argc, argv) == FAILURE)
		return (FAILURE);
	if (game_init(&game) == FAILURE)
		return (FAILURE);
	i = -1;
	while (++i < game.nb_philo)
		if (create_thread_philo(&game, i) == FAILURE)
			return (FAILRE);
	i = -1;
	while (++i < game.nb_philo)	// Bonne maniere de faire ?
		if (pthread_join((game->philo)[i]->thread, NULL)) // 2nd arg a ajuster ?
			return (ft_error(game, NULL, F_THREAD_JOIN))
	return (SUCCESS);
}