/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:37:25 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 12:07:07 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	*launch_philo(void *ptr)
{
	int				count;
	t_philosopher	*philo;

	philo = (t_philosopher*)ptr;
	count = 0;
	while (philo->game->is_over < philo->game->nb_philo &&
			philo->state != DEAD &&
			(!philo->game->nb_philo_eat || count < philo->game->nb_philo_eat))
		philo_circle(philo, &count);
	return (ptr);
}

int		create_thread_philo(t_game *game, int i)
{
	if (pthread_create(&((game->philo)[i])->thread, NULL,
						&launch_philo, (void*)((game->philo)[i])))
		return (ft_error(game, NULL, F_THREAD_CREATE));
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
		if (create_thread_philo(&game, i) == FAILURE)
			return (FAILURE);
	i = -1;
	while (++i < game.nb_philo)
		if (pthread_detach(((game.philo)[i])->thread))
			return (ft_error(&game, NULL, F_THREAD_DETACH));
	check_all_philo_dead(&game);
	i = -1;
	while (++i < game.nb_philo)
		pthread_join(((game.philo)[i])->thread, NULL);
	sem_close(game.print_sem);
	sem_close(game.fork_sem);
	return (free_all_ptr(&game));
}
