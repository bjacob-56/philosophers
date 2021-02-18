/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:35:35 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/18 13:48:09 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	launch_philo(t_philosopher *philo)
{
	int				count;

	count = 0;
	philo->time_last_meal = philo->game->start_time;
	if (pthread_create(&philo->thread, NULL,
					&check_dead_philo_background, (void*)philo))
	{
		print_error(philo->game->print_sem, F_THREAD_CREATE);
		inc_sem_end(philo->game);
	}
	if (pthread_detach(((philo->thread))))
	{
		print_error(philo->game->print_sem, F_THREAD_DETACH);
		inc_sem_end(philo->game);
	}
	while (1)
		philo_circle(philo, &count);
	sem_post(philo->game->end_sem);
}

int		create_semaphores(t_game *game)
{
	game->print_sem = NULL;
	game->fork_sem = NULL;
	game->end_sem = NULL;
	sem_unlink("/print_sem");
	sem_unlink("/fork_sem");
	sem_unlink("/end_sem");
	sem_unlink("/full_sem");
	game->print_sem = sem_open("/print_sem", O_CREAT, S_IRWXU, 1);
	if (game->print_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE, 0));
	game->fork_sem = sem_open("/fork_sem", O_CREAT, S_IRWXU, game->nb_philo);
	if (game->fork_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE, 0));
	game->end_sem = sem_open("/end_sem", O_CREAT, S_IRWXU, 0);
	if (game->end_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE, 0));
	game->full_sem = sem_open("/full_sem", O_CREAT, S_IRWXU, 1);
	if (game->full_sem == SEM_FAILED)
		return (ft_error(game, NULL, F_SEM_CREATE, 0));
	return (SUCCESS);
}

int		ft_kill_all_child(t_game *game, int nb_childs)
{
	int i;

	i = -1;
	while (++i < nb_childs)
		kill(game->tab_pid[i], SIGUSR1);
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	t_game	game;

	if (catch_arg(&game, argc, argv) == FAILURE)
		return (FAILURE);
	if (game_init(&game) == FAILURE)
		return (FAILURE);
	game.start_time = get_time();
	create_childs(&game);
	manage_childs(&game);
	ft_exit(&game);
}
