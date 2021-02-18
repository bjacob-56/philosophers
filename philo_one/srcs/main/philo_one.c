/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:32:49 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/18 09:51:06 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	*launch_philo(void *ptr)
{
	int				count;
	t_philosopher	*philo;

	philo = (t_philosopher*)ptr;
	count = 0;
	philo->time_last_meal = philo->game->start_time;
	while (philo->game->is_over < philo->game->nb_philo)
		philo_circle(philo, &count);
	return (ptr);
}

int		create_thread_philo(t_game *game, int i)
{
	if (pthread_create(&((game->philo)[i])->thread, NULL,
						&launch_philo, (void*)((game->philo)[i])))
	{
		game->is_over = game->nb_philo;
		return (print_error(game, F_THREAD_CREATE));
	}
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	t_game	game;
	int		i;

	if (catch_arg(&game, argc, argv) == FAILURE)
		return (FAILURE);
	if (game_init(&game) == FAILURE)
		return (FAILURE);
	i = -1;
	game.start_time = get_time();
	while (++i < game.nb_philo)
		create_thread_philo(&game, i);
	check_all_philo_dead(&game);
	i = -1;
	while (++i < game.nb_philo)
		pthread_join(((game.philo)[i])->thread, NULL);
	ft_exit(&game);
}
