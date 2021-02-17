/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 12:23:42 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/17 12:24:43 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int		ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*create_fork_name(t_game *game, char *str, int number)
{
	char	*name;
	char	*nbr;
	int		i;
	int		j;

	if (!(nbr = ft_itoa(number)))
		return (NULL);
	if (!(name = malloc_lst(game, ft_strlen(str) + ft_strlen(nbr) + 1)))
	{
		free(nbr);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (str[i])
		name[j++] = str[i++];
	i = 0;
	while (nbr[i])
		name[j++] = nbr[i++];
	name[j] = 0;
	return (name);
}
