#include "../../include/cub3D.h"

void  init_raycast(t_raycast *ray)
{
	ray->ray_dir.x = 0;
	ray->ray_dir.y = 0;
	ray->delta_dist.x = 0;
	ray->delta_dist.y = 0;
	ray->side_dist.x = 0;
	ray->side_dist.y = 0;
	ray->player.x = 0;
	ray->player.y = 0;
	ray->player_pos.x = 0;
	ray->player_pos.y = 0;
	ray->step_dir.x = 0;
	ray->step_dir.y = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->hit_ratio = 0;
}