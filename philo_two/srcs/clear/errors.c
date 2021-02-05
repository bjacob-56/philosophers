#include "../../includes/philosophers.h"

int	print_error(t_game *game, int error)
{
	if (error == F_NB_ARG)
		printf("Wrong number of arguments\n"); // printf
	else if (error == F_MALLOC)
		printf("A malloc failed\n");
	else if (error == F_SEM_CREATE)
		printf("The semaphore couldn't be created\n");
	else
	{
		// pthread_mutex_lock(&game->print_mutex);
		sem_wait(game->print_sem);

		if (game->is_over)
			return (SUCCESS);
		if (error == F_THREAD_CREATE)
			printf("The thread couldn't be created\n");
		else if (error == F_THREAD_JOIN)
			printf("The thread couldn't be joined\n");
		game->is_over = 1;

		// pthread_mutex_unlock(&game->print_mutex);
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
