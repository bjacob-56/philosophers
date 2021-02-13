/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 16:22:17 by bjacob            #+#    #+#             */
/*   Updated: 2021/02/13 16:22:36 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

int	ft_atoi(char *str)
{
	int	res;

	res = 0;
	while (*str == ' ')
		str++;
	while (*str >= '0' && *str <= '9')
		res = 10 * res + *(str++) - '0';
	return (res);
}
