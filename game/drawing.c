#include "../cub3d.h"

void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;
	int		offset;
	int		bytes_per_pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;

	bytes_per_pixel = mlx->bpp / 8;
	offset = (y * mlx->line_len) + (x * bytes_per_pixel);
	dst = mlx->addr + offset;
	*(unsigned int *)dst = (unsigned int)color;
}

void	draw_wall_slice(t_config *cfg, t_ray *ray, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	wall_color;

	line_height = (int)(WIN_HEIGHT / (ray->perp_wall_dist / 64.0));
	draw_start = WIN_HEIGHT / 2 - line_height / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = WIN_HEIGHT / 2 + line_height / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	wall_color = 0x00FF00;
	if (ray->side == 1)
		wall_color = wall_color / 2;
	y = draw_start;
	while (y < draw_end)
	{
		put_pixel_to_img(&cfg->mlx, x, y, wall_color);
		y++;
	}
}