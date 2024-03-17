#include "../../include/cub3D.h"

void	paint_background(t_game_info *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, game->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}
void	draw_map(t_game_info *game)
{
	(void)game;
	paint_background(game);
	return ;
}
