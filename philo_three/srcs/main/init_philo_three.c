#include "../../includes/philosophers.h"

int			catch_arg(t_game *game, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (print_error(game, F_NB_ARG));
	game->nb_philo = ft_atoi(argv[1]);
	game->t_die = ft_atoi(argv[2]);
	game->t_eat = ft_atoi(argv[3]);
	game->t_sleep = ft_atoi(argv[4]);
	game->nb_philo_eat = 0;
	if (argc == 6)
		game->nb_philo_eat = ft_atoi(argv[5]);
	// game->id_philo = 0;


// dprintf(1, "nb_philo = %d\nt_die = %d\nt_eat = %d\nt_sleep = %d\nb_philo_eat = %d\n", game->nb_philo, game->t_die, game->t_eat, game->t_sleep, game->nb_philo_eat);

	return (SUCCESS);
}

static int	philosopher_init(t_game *game, int i)
{
	t_philosopher	*philo;

	if (!(philo = malloc_lst(game, sizeof(t_philosopher))))
		return (ft_error(game, NULL, F_MALLOC));
	philo->number = i + 1;
	philo->state = THINKING;
	philo->t_die = game->t_die;
	philo->t_eat = game->t_eat;
	philo->t_sleep = game->t_sleep;
	philo->nb_philo_eat = game->nb_philo_eat;
	philo->time_last_meal = 0;
	philo->time_start_sleep = 0;
	// philo->fork_l = (game->fork)[i];
	// philo->fork_r = (game->fork)[(i + 1) % game->nb_philo];
	philo->start = game->start;
	philo->print_sem = game->print_sem;
	philo->fork_sem = game->fork_sem;
	philo->place_sem = game->place_sem;

	philo->is_over = &game->is_over;
	(game->philo)[i] = philo;
	return (SUCCESS);
}

// static int	fork_init(t_game *game, int i)
// {
// 	t_fork	*fork;

// 	if (!(fork = malloc_lst(game, sizeof(t_fork))))
// 		return (ft_error(game, NULL, F_MALLOC));
// 	fork->number = i + 1;
// 	// fork->mutex = PTHREAD_MUTEX_INITIALIZER;
// 	if (pthread_mutex_init(&fork->mutex, NULL))
// 		return (ft_error(game, NULL, F_MUTEX_CREATE));
// 	(game->fork)[i] = fork;
// 	return (SUCCESS);
// }

int			game_init(t_game *game)
{
	int		i;

	game->is_over = 0;
	game->ptrs = NULL;
	if (!(game->philo = malloc_lst(game, sizeof(t_philosopher*) * game->nb_philo)))
		return (ft_error(game, NULL, F_MALLOC));
	if (!(game->tab_pid = malloc_lst(game, sizeof(pid_t) * game->nb_philo)))
		return (ft_error(game, NULL, F_MALLOC));
	// i = -1;
	// while (++i < game->nb_philo)
	// 	if (fork_init(game, i) == FAILURE)
	// 		return (FAILURE);


///////////////////////////////////////////////////////////////////////////////// A REMETTRE SUR MAC
	game->print_sem = sem_open("/print_sem", O_CREAT, S_IRWXU, 1);
	if (game->print_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE));
	game->fork_sem = sem_open("/fork_sem", O_CREAT, S_IRWXU, game->nb_philo);
	if (game->fork_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE));
	game->place_sem = sem_open("/place_sem", O_CREAT, S_IRWXU, 1);
	if (game->place_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE));
////////////////////////////////////////////////////////////////////////////////
	// sem_t	sem1;
	// sem_t	sem2;
	// sem_t	sem3;
	// sem_init(&sem1, 0, 1);
	// sem_init(&sem2, 0, game->nb_philo);
	// sem_init(&sem3, 0, 1);
	// game->print_sem = &sem1;
	// game->fork_sem = &sem2;
	// game->place_sem = &sem3;
////////////////////////////////////////////////////////////////////////////////

	gettimeofday(&(game->start), NULL);	// valeur retour a checker ?
	i = -1;
	while (++i < game->nb_philo)
		if (philosopher_init(game, i) == FAILURE)
			return (FAILURE);

	// if (pthread_mutex_init(&game->print_mutex, NULL))
	// 	return (ft_error(game, NULL, F_MUTEX_CREATE));
	// if (pthread_mutex_init(&game->fork_mutex, NULL))
	// 	return (ft_error(game, NULL, F_MUTEX_CREATE));

	return (SUCCESS);
}