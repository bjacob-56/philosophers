/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:32:49 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/16 16:24:03 by bjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	*launch_philo(void *ptr)
{
	int				count;
	t_philosopher *philo;

	philo = (t_philosopher*)ptr;
	count = 0;
	while (*philo->is_over < philo->nb_philo &&
		(!philo->nb_philo_eat || count < philo->nb_philo_eat))
		philo_circle(philo, &count);
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
	while (++i < game.nb_philo)
		if (pthread_detach(((game.philo)[i])->thread)) // 2nd arg a ajuster ?
			return (ft_error(&game, NULL, F_THREAD_DETACH));
	check_all_philo_dead(&game);
	i = -1;
	while (++i < game.nb_philo)
		pthread_join(((game.philo)[i])->thread, NULL); // 2nd arg a ajuster ?
	return (free_all_ptr(&game));
}

// int	main(int argc, char **argv)
// {
// 	t_game	*game;
// 	int		i;

// 	game = malloc(sizeof(t_game));	
// 	if (catch_arg(game, argc, argv) == FAILURE)
// 		return (FAILURE);
// 	if (game_init(game) == FAILURE)
// 		return (FAILURE);
// 	i = -1;
// 	while (++i < game->nb_philo)
// 		if (create_thread_philo(game, i) == FAILURE)
// 			return (FAILURE);
// 	i = -1;
// 	while (++i < game->nb_philo)
// 		if (pthread_detach(((game->philo)[i])->thread)) // 2nd arg a ajuster ?
// 			return (ft_error(game, NULL, F_THREAD_DETACH));
// 	check_all_philo_dead(game);
// 	// while (++i < game.nb_philo)
// 	// 	if (pthread_join(((game.philo)[i])->thread, NULL)) // 2nd arg a ajuster ?
// 	// 		return (ft_error(&game, NULL, F_THREAD_JOIN));
// 	return (free_all_ptr(game));

// 	// return(0);
// }