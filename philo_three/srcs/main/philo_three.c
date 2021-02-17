/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:35:35 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 15:35:00 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	launch_philo(t_philosopher *philo)
{
	int				count;

	count = 0;
	if (pthread_create(&philo->thread, NULL,
					&check_dead_philo_background, (void*)philo))
	{
		print_error(philo->game->print_sem, F_THREAD_CREATE);
		exit(DEAD);
	}
	if (pthread_detach(((philo->thread))))
	{
		print_error(philo->game->print_sem, F_THREAD_DETACH);
		exit(DEAD);
	}
	while ((!philo->game->nb_philo_eat || count < philo->game->nb_philo_eat))
		philo_circle(philo, &count);
	sem_post(philo->game->end_sem);
	while (1)
	{
		philo->time_last_meal = get_time();
		usleep(1000);
	}
}

int		ft_kill_all_child(t_game *game)
{
	int i;

	i = -1;
	while (++i < game->nb_philo)
		kill(game->tab_pid[i], SIGKILL);
	return (SUCCESS);
}

int		create_and_manage_childs(t_game *game)
{
	int		i;
	pid_t	program;

	i = -1;
	while (++i < game->nb_philo)
	{
		if ((program = fork()) == -1)
			return (ft_error(game, NULL, F_FORK_CREATE, game->nb_philo));
		if (!program)
			launch_philo((game->philo)[i]);
		else
			game->tab_pid[i] = program;
	}
	i = -1;
	while (++i < game->nb_philo)
		sem_wait(game->end_sem);
	i = -1;
	while (++i < game->nb_philo)
		kill(game->tab_pid[i], SIGKILL);
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
	create_and_manage_childs(&game);
	ft_exit(&game);
}
