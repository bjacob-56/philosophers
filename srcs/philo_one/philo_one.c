#include "../../includes/philosophers.h"

// void	*launch_philo(t_philosopher *philo)
void	*launch_philo(void *ptr)
{
	int				count;
	t_philosopher *philo;

	philo = (t_philosopher*)ptr;
	gettimeofday(&(philo->start), NULL);	// valeur retour a checker ?

	count = 0;
	while (philo->state != DEAD &&
		(!philo->nb_philo_eat || count < philo->nb_philo_eat))
	{
		check_dead(philo);
		if (philo->state == THINKING)
			philo_eat(philo, &count);
		if (philo->state == EATING)
			philo_sleep(philo);
		if (philo->state == SLEEPING)
			philo_think(philo);
	}
	return (ptr);	// quelle valeur ?
}

int	create_thread_philo(t_game *game, int i)
{
	if (pthread_create(&((game->philo)[i])->thread, NULL, &launch_philo, (void*)((game->philo)[i])))
		return (ft_error(game, NULL, F_THREAD_CREATE));
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;
	
	if (catch_arg(&game, argc, argv) == FAILURE)
		return (FAILURE);
	if (game_init(&game) == FAILURE)
		return (FAILURE);
	i = -1;
	while (++i < game.nb_philo)
		if (create_thread_philo(&game, i) == FAILURE)
			return (FAILURE);
	i = -1;
	while (++i < game.nb_philo)	// Bonne maniere de faire ?
		if (pthread_join(((game.philo)[i])->thread, NULL)) // 2nd arg a ajuster ?
			return (ft_error(&game, NULL, F_THREAD_JOIN));
	return (free_all_ptr(&game));
}