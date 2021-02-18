/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:37:09 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/18 13:46:51 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void		check_args_init(t_game *game, int argc)
{
	if (!game->nb_philo || !game->t_die || !game->t_eat || !game->t_sleep)
		exit(SUCCESS);
	if (argc == 6 && !game->nb_philo_eat)
	{
		printf("0 Every philosopher has eaten 0 times\n");
		exit(SUCCESS);
	}
	if (game->nb_philo == 1)
	{
		usleep(1000 * game->t_die);
		printf("%d %d died\n", game->t_die, 1);
		exit(SUCCESS);
	}
}

int			catch_arg(t_game *game, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (print_error(NULL, F_NB_ARG));
	game->nb_philo = ft_atoi(argv[1]);
	game->t_die = ft_atoi(argv[2]);
	game->t_eat = ft_atoi(argv[3]);
	game->t_sleep = ft_atoi(argv[4]);
	game->nb_philo_eat = 0;
	if (argc == 6)
		game->nb_philo_eat = ft_atoi(argv[5]);
	check_args_init(game, argc);
	return (SUCCESS);
}

static int	philosopher_init(t_game *game, int i)
{
	t_philosopher	*philo;

	if (!(philo = malloc_lst(game, sizeof(t_philosopher))))
		return (ft_error(game, NULL, F_MALLOC));
	philo->number = i + 1;
	philo->state = THINKING;
	philo->time_last_meal = 0;
	philo->time_start_sleep = 0;
	philo->game = game;
	(game->philo)[i] = philo;
	return (SUCCESS);
}

int			game_init(t_game *game)
{
	int		i;

	game->next_philo_eat = 1;
	game->is_over = 0;
	game->ptrs = NULL;
	game->print_sem = NULL;
	game->fork_sem = NULL;
	if (!(game->philo = malloc_lst(game,
								sizeof(t_philosopher*) * game->nb_philo)))
		return (ft_error(game, NULL, F_MALLOC));
	sem_unlink("/print_sem");
	game->print_sem = sem_open("/print_sem", O_CREAT, S_IRWXU, 1);
	if (game->print_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE));
	sem_unlink("/fork_sem");
	game->fork_sem = sem_open("/fork_sem", O_CREAT, S_IRWXU, game->nb_philo);
	if (game->fork_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE));
	i = -1;
	while (++i < game->nb_philo)
		if (philosopher_init(game, i) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}
