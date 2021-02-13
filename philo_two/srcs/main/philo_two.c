/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:37:25 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/13 17:49:57 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	*launch_philo(void *ptr)
{
	int				count;
	t_philosopher	*philo;

	philo = (t_philosopher*)ptr;
	count = 0;
	while (!*(philo->is_over) && philo->state != DEAD &&
		(!philo->nb_philo_eat || count < philo->nb_philo_eat))
	{
		if (philo->state == THINKING)
			philo_eat(philo, &count);
		else if (philo->state == EATING)
			philo_sleep(philo);
		else if (philo->state == SLEEPING)
			philo_think(philo);
	}

	return (ptr);
}

int	create_thread_philo(t_game *game, int i)
{
	if (pthread_create(&((game->philo)[i])->thread, NULL, &launch_philo, (void*)((game->philo)[i])))
		return (ft_error(game, NULL, F_THREAD_CREATE));
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;
	int		i;
	
	if (catch_arg(&game, argc, argv) == FAILURE)
		return (FAILURE);
	if (game_init(&game) == FAILURE)
		return (FAILURE);
	i = -1;
	while (++i < game.nb_philo)
		if (create_thread_philo(&game, i) == FAILURE)
			return (FAILURE);
	i = -1;
	while (++i < game.nb_philo)	// Bonne maniere de faire ?
		if (pthread_join(((game.philo)[i])->thread, NULL)) // 2nd arg a ajuster ?
			return (ft_error(&game, NULL, F_THREAD_JOIN));

	sem_close(game.print_sem);
	sem_close(game.fork_sem);
	sem_close(game.place_sem);

	return (free_all_ptr(&game));
}
