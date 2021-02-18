/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:54:18 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/18 08:33:15 by bjacob           ###   ########lyon.fr   */
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

int		clear_all_mutex(t_game *game, int nb_fork_created)
{
	int	i;

	pthread_mutex_destroy(&game->print_mutex);
	i = -1;
	while (++i < nb_fork_created)
		pthread_mutex_destroy(&game->fork[i]->mutex);
	return (SUCCESS);
}

int		free_all_ptr(t_game *game)
{
	ft_lstclear(&game->ptrs, free);
	return (SUCCESS);
}

void	ft_exit(t_game *game)
{
	clear_all_mutex(game, game->nb_philo);
	free_all_ptr(game);
	exit(SUCCESS);
}
