#include "../../include/cub3D.h"

void	dda(t_game_info *game, t_raycast *ray)
{
	int hit_flag;

	hit_flag = 0;
	while (hit_flag == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)	// side_dist.x 로 결정
		{
			ray->side = DECIDE_W_OR_E;	// 수직으로 맞음
			ray->side_dist.x += ray->delta_dist.x;
			ray->player_pos.x += ray->step_dir.x;
		}
		else
		{
			ray->side = DECIDE_N_OR_S;	// 수평으로 맞음
			ray->side_dist.y += ray->delta_dist.y;
			ray->player_pos.y += ray->step_dir.y;
		}
		if (game->map[ray->player_pos.y][ray->player_pos.x] != '0')
			hit_flag = 1;
	}
}