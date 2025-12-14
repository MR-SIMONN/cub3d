#include "../cub3d.h"

void	perform_dda(t_config *cfg, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cfg->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void	draw_wall_slice(t_config *cfg, t_ray *ray, int x)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	y;
	int	wall_color;

	line_height = (int)(WIN_HEIGHT / (ray->perp_wall_dist / 64.0));
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
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

void	calculate_ray_casting(t_config *cfg)
{
    int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray_data(cfg, &ray, x);
		init_step_sidedist(cfg, &ray);
		perform_dda(cfg, &ray);
		draw_wall_slice(cfg, &ray, x);
		x++;
	}
}

void	draw_floor_ceiling(t_config *cfg)
{
	int	x;
	int	y;
	int	floor_color;
	int	ceiling_color;

	floor_color = (cfg->floor.r << 16) | (cfg->floor.g << 8) | cfg->floor.b;
	ceiling_color = (cfg->ceiling.r << 16) | (cfg->ceiling.g << 8) | cfg->ceiling.b;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				put_pixel_to_img(&cfg->mlx, x, y, ceiling_color);
			else
				put_pixel_to_img(&cfg->mlx, x, y, floor_color);
			x++;
		}
		y++;
	}
}

int	render_frame(t_config *cfg)
{
	if (!cfg->mlx.win)
		return (1);

	draw_floor_ceiling(cfg);
	calculate_ray_casting(cfg);
	mlx_put_image_to_window(cfg->mlx.mlx, cfg->mlx.win, cfg->mlx.img, 0, 0);

	return (0);
}