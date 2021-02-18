/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:18:44 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/18 08:33:24 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	*add_lst_to_free(t_game *game, void *ptr)
{
	t_list	*elem;

	if (!(elem = ft_lstnew(ptr)))
	{
		free(ptr);
		return (NULL);
	}
	if (!(game->ptrs))
		game->ptrs = elem;
	else
		ft_lstadd_back(&game->ptrs, elem);
	return (ptr);
}

void	*malloc_lst(t_game *game, int size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		return (NULL);
	if (!add_lst_to_free(game, ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

int		clear_all_semaphores(t_game *game, int nb_fork_created)
{
	int	i;

	sem_close(game->print_sem);
	sem_close(game->fork_sem);
	i = -1;
	while (++i < nb_fork_created)
		sem_close(game->fork[i]->private_fork_sem);
	return (SUCCESS);
}

int		free_all_ptr(t_game *game)
{
	ft_lstclear(&game->ptrs, free);
	return (SUCCESS);
}

void	ft_exit(t_game *game)
{
	clear_all_semaphores(game, game->nb_philo);
	free_all_ptr(game);
	exit(SUCCESS);
}
