#include "../../include/cub3D.h"

void	control_player(t_game_info *game)
{
	if (game->move_flag.no == TRUE || game->move_flag.so == TRUE \
		|| game->move_flag.ea == TRUE || game->move_flag.we == TRUE)
		move_player(game);
	else if (game->move_flag.r == TRUE || game->move_flag.l == TRUE)
		rotate_player(game);
}
