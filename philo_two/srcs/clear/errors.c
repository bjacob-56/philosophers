/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:26:32 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/16 16:18:05 by bjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	print_error(t_game *game, int error)
{
	if (error == F_NB_ARG)
		printf("Wrong number of arguments\n");
	else if (error == F_MALLOC)
		printf("A malloc failed\n");
	else if (error == F_SEM_CREATE)
		printf("The semaphore couldn't be created\n");
	else
	{
		sem_wait(game->print_sem);
		if (game->is_over == game->nb_philo)
			return (SUCCESS);
		if (error == F_THREAD_CREATE)
			printf("The thread couldn't be created\n");
		else if (error == F_THREAD_DETACH)
			printf("The thread couldn't be detached\n");
		else if (error == F_THREAD_JOIN)
			printf("The thread couldn't be joined\n");
		game->is_over = game->nb_philo;
		sem_post(game->print_sem);
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
