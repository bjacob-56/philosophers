/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:32:21 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 14:08:32 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
	return (SUCCESS);
}

static int	philosopher_init(t_game *game, int i)
{
	t_philosopher	*philo;

	if (!(philo = malloc_lst(game, sizeof(t_philosopher))))
		return (ft_error(game, NULL, F_MALLOC, game->nb_philo));
	philo->number = i + 1;
	philo->state = THINKING;
	philo->time_last_meal = 0;
	philo->time_start_sleep = 0;
	philo->fork_l = (game->fork)[i];
	philo->fork_r = (game->fork)[(i + 1) % game->nb_philo];
	philo->game = game;
	(game->philo)[i] = philo;
	return (SUCCESS);
}

static int	fork_init(t_game *game, int i)
{
	t_fork	*fork;

	if (!(fork = malloc_lst(game, sizeof(t_fork))))
		return (ft_error(game, NULL, F_MALLOC, i));
	fork->number = i + 1;
	if (pthread_mutex_init(&fork->mutex, NULL))
		return (ft_error(game, NULL, F_MUTEX_CREATE, i));
	fork->last_philo = -1;
	(game->fork)[i] = fork;
	return (SUCCESS);
}

int			game_init(t_game *game)
{
	int		i;

	game->is_over = 0;
	game->ptrs = NULL;
	if (!(game->philo = malloc_lst(game,
								sizeof(t_philosopher*) * game->nb_philo)))
		return (ft_error(game, NULL, F_MALLOC, 0));
	if (!(game->fork = malloc_lst(game, sizeof(t_fork*) * game->nb_philo)))
		return (ft_error(game, NULL, F_MALLOC, 0));
	if (pthread_mutex_init(&game->print_mutex, NULL))
		return (ft_error(game, NULL, F_MUTEX_CREATE, 0));
	i = -1;
	while (++i < game->nb_philo)
		if (fork_init(game, i) == FAILURE)
			return (FAILURE);
	i = -1;
	while (++i < game->nb_philo)
		if (philosopher_init(game, i) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}
