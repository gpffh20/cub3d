#include "../../include/cub3D.h"

static void rotate_to_right(t_game_info *game)
{
	t_point_double old_dir;
	t_point_double old_plane;
	double	rad;

	rad = asin(tan(M_PI / 6)) * (-ROTATE_SPEED);
	old_dir.x = game->view_dir.x;
	old_dir.y = game->view_dir.y;
	old_plane.x = game->plane.x;
	old_plane.y = game->plane.y;
	game->view_dir.x = old_dir.x * cos(rad) - old_dir.y * sin(rad);
	game->view_dir.y = old_dir.x * sin(rad) + old_dir.y * cos(rad);
	game->plane.x = old_plane.x * cos(rad) - old_plane.y * sin(rad);
	game->plane.y = old_plane.x * sin(rad) + old_plane.y * cos(rad);
}

static void rotate_to_left(t_game_info *game)
{
	t_point_double old_dir;
	t_point_double old_plane;
	double	rad;

	rad = asin(tan(M_PI / 6)) * ROTATE_SPEED;
	old_dir.x = game->view_dir.x;
	old_dir.y = game->view_dir.y;
	old_plane.x = game->plane.x;
	old_plane.y = game->plane.y;
	game->view_dir.x = old_dir.x * cos(rad) - old_dir.y * sin(rad);
	game->view_dir.y = old_dir.x * sin(rad) + old_dir.y * cos(rad);
	game->plane.x = old_plane.x * cos(rad) - old_plane.y * sin(rad);
	game->plane.y = old_plane.x * sin(rad) + old_plane.y * cos(rad);
}

void rotate_player(t_game_info *game)
{
	if (game->move_flag.r == TRUE)
		rotate_to_right(game);
	else if (game->move_flag.l == TRUE)
		rotate_to_left(game);
}