/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:19:16 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/13 16:19:28 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	print_error(t_game *game, int error)
{
	if (error == F_NB_ARG)
		printf("Wrong number of arguments\n");
	else if (error == F_MALLOC)
		printf("A malloc failed\n");
	else if (error == F_MUTEX_CREATE)
		printf("The mutex couldn't be created\n");
	else
	{
		pthread_mutex_lock(&game->print_mutex);
		if (game->is_over == game->nb_philo)
			return (SUCCESS);
		if (error == F_THREAD_CREATE)
			printf("The thread couldn't be created\n");
		else if (error == F_THREAD_DETACH)
			printf("The thread couldn't be detached\n");
		game->is_over = game->nb_philo;
		pthread_mutex_unlock(&game->print_mutex);
	}
	return (FAILURE);
}

int	ft_error(t_game *game, void *ptr, int error)
{
	free(ptr);
	free_all_ptr(game);
	print_error(game, error);
	return (FAILURE);
}
