#include "../../include/cub3D.h"

void	mlx_pixel_put_once(t_texture *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}