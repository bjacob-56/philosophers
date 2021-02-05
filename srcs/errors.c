#include "../includes/philosophers.h"

int	print_error(int error)
{
	if (error == F_NB_ARG)
		printf("Wrong number of arguments\n"); // printf
	else if (error == F_MALLOC)
		printf("A malloc failed\n");
	return (FAILURE);
}

int	ft_error(t_game *game, void *ptr, int error)
{
	free(ptr);
	free_all_ptr(game);
	print_error(error);
	return (FAILURE);
}