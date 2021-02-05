#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_game	game;
	
	if (catch_arg(game, argc, argv) == FAILURE)
		return (FAILURE);
	if (game_init(&game) == FAILURE)
		return (FAILURE);
	
}