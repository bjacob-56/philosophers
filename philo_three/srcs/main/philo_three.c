#include "../../includes/philosophers.h"

void	*launch_philo(void *ptr)
{
	int				count;
	t_philosopher *philo;

	philo = (t_philosopher*)ptr;
	count = 0;
	while (!*(philo->is_over) && philo->state != DEAD &&
		(!philo->nb_philo_eat || count < philo->nb_philo_eat))
	{
		if (philo->state == THINKING)
			philo_eat(philo, &count);
		else if (philo->state == EATING)
			philo_sleep(philo);
		else if (philo->state == SLEEPING)
			philo_think(philo);
	}
	exit(SUCCESS);
	return (ptr);
}

int	create_fork_philo(t_game *game, int i)
{
	launch_philo((void*)((game->philo)[i]));
	// if (pthread_create(&((game->philo)[i])->thread, NULL, &launch_philo, (void*)((game->philo)[i])))
	// 	return (ft_error(game, NULL, F_THREAD_CREATE));
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;
	pid_t 	program;
	int		status;
	
	if (catch_arg(&game, argc, argv) == FAILURE)
		return (FAILURE);
	if (game_init(&game) == FAILURE)
		return (FAILURE);
	i = -1;
	while (++i < game.nb_philo)
	{
		if ((program = fork()) == -1)	// gestion des childs deja crees avant
			return (ft_error(&game, NULL, F_FORK_CREATE));
		if (!program)
			return (create_fork_philo(&game, i));
		else
			game.tab_pid[i] = program;
	}
	waitpid(-1, &status, 0);
	i = -1;
	while (++i < game.nb_philo)	// Bonne maniere de faire ?
		kill(game.tab_pid[i], SIGKILL);
	return (free_all_ptr(&game));
}