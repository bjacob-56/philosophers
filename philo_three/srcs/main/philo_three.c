/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:35:35 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/18 10:58:28 by bjacob           ###   ########lyon.fr   */
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
