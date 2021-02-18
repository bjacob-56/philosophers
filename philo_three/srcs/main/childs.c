/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 17:21:20 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/18 10:59:37 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	*check_full(void *ptr)
{
	t_game *game;

	game = (t_game*)ptr;
	sem_wait(game->full_sem);
	sem_wait(game->print_sem);
	printf("%d Every philosopher has eaten %d times\n",
			get_time() - game->start_time,
			game->nb_philo_eat);
	return (ptr);
}

int		print_full(t_game *game)
{
	pthread_t	thread_full;

	if (pthread_create(&thread_full, NULL,
					&check_full, (void*)game))
		printf("The thread couldn't be created\n");
	else if (pthread_detach(((thread_full))))
		printf("The thread couldn't be detached\n");
	usleep(1000 * 50);
	return (SUCCESS);
}

int		create_childs(t_game *game)
{
	int		i;
	pid_t	program;

	i = -1;
	while (++i < game->nb_philo)
	{
		if ((program = fork()) == -1)
		{
			ft_kill_all_child(game, i);
			return (ft_error(game, NULL, F_FORK_CREATE, game->nb_philo));
		}
		if (!program)
			launch_philo((game->philo)[i]);
		else
			game->tab_pid[i] = program;
	}
	return (SUCCESS);
}

void	*check_childs(void *ptr)
{
	int		status;
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
	print_full(game);
	ft_kill_all_child(game, game->nb_philo);
	return (SUCCESS);
}
