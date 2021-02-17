/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:25:40 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 14:14:11 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	print_error(sem_t *print_sem, int error) // a reprendre
{
	if (error == F_NB_ARG)
		printf("Wrong number of arguments\n");
	else if (error == F_MALLOC)
		printf("A malloc failed\n");
	else if (error == F_SEM_CREATE)
		printf("The semaphore couldn't be created\n");
	else if (error == F_THREAD_CREATE)
		printf("The thread couldn't be created\n");
	else if (error == F_THREAD_DETACH)
		printf("The thread couldn't be detached\n");
	else
	{
		sem_wait(print_sem);
		if (error == F_FORK_CREATE)
			printf("The fork couldn't be created\n");
		sem_post(print_sem);
	}
	return (FAILURE);
}

int	ft_error(t_game *game, void *ptr, int error, int nb_fork_created)
{
	free(ptr);
	clear_all_semaphores(game, nb_fork_created);
	free_all_ptr(game);
	print_error(game->print_sem, error);
	return (FAILURE);
}
