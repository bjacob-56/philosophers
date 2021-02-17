/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:35:35 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 08:56:46 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	launch_philo(t_philosopher *philo)
{
	int				count;

	count = 0;
	if (pthread_create(&philo->thread, NULL, &check_dead_philo_background, (void*)philo))
	{
		print_error(philo->print_sem, F_THREAD_CREATE);
		exit (DEAD);
	}
	if (pthread_detach(((philo->thread))))
	{
		print_error(philo->print_sem, F_THREAD_DETACH);
		exit (DEAD);
	}
	while ((!philo->nb_philo_eat || count < philo->nb_philo_eat))
		philo_circle(philo, &count);
	exit(SUCCESS);
}

int	ft_kill_all_child(t_game *game)
{
	int i;

	i = -1;
	while (++i < game->nb_philo)
		kill(game->tab_pid[i], SIGKILL);
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
			launch_philo((game.philo)[i]);
		else
			game.tab_pid[i] = program;
	}

	i = -1;
	while (++i < game.nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == DEAD)
			ft_kill_all_child(&game);
	}

	i = -1;
	while (++i < game.nb_philo)	// Bonne maniere de faire ?
		kill(game.tab_pid[i], SIGKILL);

	sem_close(game.print_sem);
	sem_close(game.fork_sem);
	sem_close(game.place_sem);

	return (free_all_ptr(&game));
}
