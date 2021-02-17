/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:35:19 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 15:23:19 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

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
	return (SUCCESS);
}

static int	philosopher_init(t_game *game, int i)
{
	t_philosopher	*philo;

	if (!(philo = malloc_lst(game, sizeof(t_philosopher))))
		return (ft_error(game, NULL, F_MALLOC, game->nb_philo));
	philo->number = i + 1;
	philo->time_last_meal = 0;
	philo->time_start_sleep = 0;
	philo->next_philo_eat = &game->next_philo_eat;
	philo->game = game;
	(game->philo)[i] = philo;
	return (SUCCESS);
}

static int	fork_init(t_game *game, int i)
{
	t_fork	*fork;
	char	*fork_name;

	if (!(fork = malloc_lst(game, sizeof(t_fork))))
		return (ft_error(game, NULL, F_MALLOC, i));
	fork->number = i + 1;
	if (!(fork_name = create_fork_name(game, "/fork_sem", i)))
		return (ft_error(game, NULL, F_MALLOC, i));
	sem_unlink(fork_name);	//
	fork->private_fork_sem = sem_open(fork_name, O_CREAT, S_IRWXU, 0);
	// fork->private_fork_sem = sem_open(fork_name, O_CREAT, S_IRWXU, 1);
	// fork->private_fork_sem = sem_open(fork_name, O_CREAT | O_EXCL, 420, 1);
	if (fork->private_fork_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE, i));
	// sem_wait(fork->private_fork_sem);
	(game->fork)[i] = fork;
	return (SUCCESS);
}

static int	create_semaphores(t_game *game)
{
	game->print_sem = NULL;
	game->fork_sem = NULL;
	sem_unlink("/print_sem");
	sem_unlink("/fork_sem");
	game->print_sem = sem_open("/print_sem", O_CREAT, S_IRWXU, 1);
	// game->print_sem = sem_open("/print_sem", O_CREAT | O_EXCL, 420, 1);
	if (game->print_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE, 0));
	game->fork_sem = sem_open("/fork_sem", O_CREAT, S_IRWXU, game->nb_philo);
	// game->fork_sem = sem_open("/fork_sem", O_CREAT | O_EXCL, 420, game->nb_philo);
	if (game->fork_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE, 0));
	return (SUCCESS);
}

int			game_init(t_game *game)
{
	int		i;

	game->next_philo_eat = 1;
	game->ptrs = NULL;
	if (!(game->philo = malloc_lst(game,
			sizeof(t_philosopher*) * game->nb_philo)))
		return (ft_error(game, NULL, F_MALLOC, 0));
	if (!(game->fork = malloc_lst(game, sizeof(t_fork*) * game->nb_philo)))
		return (ft_error(game, NULL, F_MALLOC, 0));
	if (!(game->tab_pid = malloc_lst(game, sizeof(pid_t) * game->nb_philo)))
		return (ft_error(game, NULL, F_MALLOC, 0));		
	if (create_semaphores(game) == FAILURE)
		return (FAILURE);
	i = -1;
	while (++i < game->nb_philo)
		if (fork_init(game, i) == FAILURE)
			return (FAILURE);
	sem_post(game->fork[0]->private_fork_sem);
	i = -1;
	while (++i < game->nb_philo)
		if (philosopher_init(game, i) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}
