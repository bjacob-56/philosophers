#include "../includes/philosophers.h"

int	launch_philo(t_philosopher *philo)
{

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