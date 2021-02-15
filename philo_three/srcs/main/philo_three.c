/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:35:35 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/13 17:55:26 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	*launch_philo(void *ptr)
{
	int				count;
	t_philosopher *philo;

	philo = (t_philosopher*)ptr;
	count = 0;
	while (*philo->is_over < philo->nb_philo && philo->state != DEAD &&
		(!philo->nb_philo_eat || count < philo->nb_philo_eat))
		philo_circle(philo, &count);
	exit(SUCCESS);
	// return (ptr);
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
	// int		status;
	
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
	while (game.is_over < game.nb_philo)
		check_all_philo_dead(&game);

///		gestion a faire pour s'arreter avant mais pas trop tot
	// i = -1;
	// while (++i < game.nb_philo)
		// waitpid(-1, &status, 0);
///
	i = -1;
	while (++i < game.nb_philo)	// Bonne maniere de faire ?
		kill(game.tab_pid[i], SIGKILL);

	sem_close(game.print_sem);
	sem_close(game.fork_sem);
	sem_close(game.place_sem);
		
	return (free_all_ptr(&game));
}
