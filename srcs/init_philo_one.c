#include "../includes/philosophers.h"

int			catch_arg(t_game *game, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (print_error(F_NB_ARG));
	game->nb_philo = ft_atoi(argv[1]);
	game->t_die = ft_atoi(argv[2]);
	game->t_eat = ft_atoi(argv[3]);
	game->t_sleep = ft_atoi(argv[4]);
	game->nb_philo_eat = 0;
	if (argc == 6)
		game->nb_philo_eat = ft_atoi(argv[5]);
	return (SUCCESS);
}

static int	philosopher_init(t_game *game, int i)
{
	t_philosopher	*philo;
	t_list			*elem;

	if (!(philo = malloc_lst(game, sizeof(t_philosopher))))
		return (ft_error(game, NULL, F_MALLOC));
	philo->number = i + 1;
	philo->last_meal = 0;
	if (!(elem = ft_lstnew(philo)) || !add_lst_to_free(game, elem))
		return (ft_error(game, elem, F_MALLOC));
	ft_lstadd_back(&game->philo, elem);
	return (SUCCESS);
}

static int	fork_init(t_game *game, int i)
{
	t_fork	*fork;
	t_list	*elem;

	if (!(fork = malloc_lst(game, sizeof(t_fork))))
		return (ft_error(game, NULL, F_MALLOC));
	fork->number = i + 1;
	if (!(elem = ft_lstnew(fork)) || !add_lst_to_free(game, elem))
		return (ft_error(game, elem, F_MALLOC));
	ft_lstadd_back(&game->fork, elem);
	return (SUCCESS);
}

int			game_init(t_game *game)
{
	int		i;

	game.ptrs = NULL;
	game->philo = NULL;
	game->fork = NULL;
	i = -1;
	while (++i < game->nb_philo)
	{
		if (philosopher_init(game, i) == FAILURE ||
			fork_init(game, i) == FAILURE)
			return (FALURE);
	}
}	return (SUCCESS);