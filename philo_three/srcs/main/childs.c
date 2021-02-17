/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:21:20 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 17:43:56 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"


int		create_childs(t_game *game)
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
	return (SUCCESS);
}

void	*check_childs(void *ptr)
{
	int	status;
	t_game	*game;

	game = (t_game*)ptr;
	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status) == 1 &&
		WTERMSIG(status) != SIGUSR1)
	{
		print_error(game->print_sem, F_CHILD_KILLED);
		inc_sem_end(game);
	}
	return (ptr);
}

int		manage_childs(t_game *game)
{
	int			i;
	pthread_t	thread_childs;
	
	if (pthread_create(&thread_childs, NULL,
					&check_childs, (void*)game))
	{
		print_error(game->print_sem, F_THREAD_CREATE);
		inc_sem_end(game);
	}
	if (pthread_detach(((thread_childs))))
	{
		print_error(game->print_sem, F_THREAD_DETACH);
		inc_sem_end(game);
	}
	i = -1;
	while (++i < game->nb_philo)
		sem_wait(game->end_sem);
	i = -1;
	while (++i < game->nb_philo)
		kill(game->tab_pid[i], SIGUSR1);
	return (SUCCESS);
}

