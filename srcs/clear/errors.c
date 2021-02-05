#include "../../includes/philosophers.h"

int	print_error(int error)
{
	if (error == F_NB_ARG)
		printf("Wrong number of arguments\n"); // printf
	else if (error == F_MALLOC)
		printf("A malloc failed\n");
	else if (error == F_THREAD_CREATE)
		printf("The thread couldn't be created\n");
	else if (error == F_THREAD_JOIN)
		printf("The thread couldn't be joined\n");
	else if (error == F_MUTEX_CREATE)
		printf("The mutex couldn't be created\n");
	return (FAILURE);
}

int	ft_error(t_game *game, void *ptr, int error)
{
	free(ptr);
	free_all_ptr(game);
	print_error(error);
	return (FAILURE);
}