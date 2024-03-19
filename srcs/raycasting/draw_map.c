#include "../../include/cub3D.h"

int	draw_map(t_game_info *game)
{
	int	monitor;

	monitor = 0;
	paint_background(game);
	control_player(game);
	while (monitor < SCREEN_WIDTH)
	{
		calc_ray_params(game, &game->ray, monitor);
		init_vectors(&game->ray, game);
		dda(game, &game->ray);
		choose_texture(game, &game->ray);
		calc_wall_length(game, &game->ray);
		draw_texture(game, monitor);
		monitor++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->window.img, 0, 0);
	return (SUCCESS);
}
