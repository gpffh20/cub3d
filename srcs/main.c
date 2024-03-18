#include "../include/cub3D.h"

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

int check_xpm(t_game_info *game)
{
	int fd;

	fd = open(game->no_path, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		return (FAIL);
	fd = open(game->so_path, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		return (FAIL);
	fd = open(game->we_path, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		return (FAIL);
	fd = open(game->ea_path, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		return (FAIL);
	return (SUCCESS);
}

void init_texture(t_game_info *game)
{
	if (check_xpm(game) == FAIL)
		error_exit("Error: Invalid texture file.\n");
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	game->window.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->window.addr = mlx_get_data_addr(game->window.img, &game->window.bpp, &game->window.line_length, &game->window.endian);
	game->no_texture.img = mlx_xpm_file_to_image(game->mlx, game->no_path, &game->no_texture.width, &game->no_texture.height);
	game->no_texture.addr = mlx_get_data_addr(game->no_texture.img, &game->no_texture.bpp, &game->no_texture.line_length, &game->no_texture.endian);
	game->so_texture.img = mlx_xpm_file_to_image(game->mlx, game->so_path, &game->so_texture.width, &game->so_texture.height);
	game->so_texture.addr = mlx_get_data_addr(game->so_texture.img, &game->so_texture.bpp, &game->so_texture.line_length, &game->so_texture.endian);
	game->we_texture.img = mlx_xpm_file_to_image(game->mlx, game->we_path, &game->we_texture.width, &game->we_texture.height);
	game->we_texture.addr = mlx_get_data_addr(game->we_texture.img, &game->we_texture.bpp, &game->we_texture.line_length, &game->we_texture.endian);
	game->ea_texture.img = mlx_xpm_file_to_image(game->mlx, game->ea_path, &game->ea_texture.width, &game->ea_texture.height);
	game->ea_texture.addr = mlx_get_data_addr(game->ea_texture.img, &game->ea_texture.bpp, &game->ea_texture.line_length, &game->ea_texture.endian);
	mlx_put_image_to_window(game->mlx, game->win, game->window.img, 0, 0);
	// mlx_put_image_to_window(game->mlx, game->win, game->no_texture.img, 0, 0);
}

void	init_game(t_game_info *game)
{
	init_raycast(&game->ray);
	game->perp_wall_dist = 0;
	game->view_dir.x = 0;
	game->view_dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player_cnt = 0;
	game->map_start = 0;
	game->ceiling_color = -1;
	game->floor_color = -1;
	game->no_path = NULL;
	game->so_path = NULL;
	game->we_path = NULL;
	game->ea_path = NULL;
}

int	exit_game(t_game_info *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

int main(int ac, char **av)
{
	t_game_info game;

	if (ac != 2)
		error_exit("Error: Wrong number of arguments.\n");
	invalid_file(av[1]);
	init_game(&game);
	get_info(av[1], &game);
	get_map(av[1], &game);
	init_texture(&game);
	mlx_loop_hook(game.mlx, &draw_map, &game);
//	mlx_hook(game.win, KEY_PRESS, 0, &key_press, &game);
//	mlx_hook(game.win, KEY_RELEASE, 0, &key_release, &game);
//	mlx_key_hook(game.win, &exit_game, &game);
	mlx_loop(game.mlx);
	return (0);
}
