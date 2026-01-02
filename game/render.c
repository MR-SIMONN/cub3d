/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 10:09:52 by moel-hai          #+#    #+#             */
/*   Updated: 2026/01/01 10:09:52 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		draw_textured_wall(cfg, &ray, x);
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
	ceiling_color = (cfg->ceiling.r << 16) | (cfg->ceiling.g << 8)
		| cfg->ceiling.b;
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
	if (!cfg->tex_no.img || !cfg->tex_so.img
		|| !cfg->tex_we.img || !cfg->tex_ea.img)
	{
		printf("Error: Textures not loaded\n");
		return (1);
	}
	keys_update(cfg);
	draw_floor_ceiling(cfg);
	calculate_ray_casting(cfg);
	mlx_put_image_to_window(cfg->mlx.mlx, cfg->mlx.win, cfg->mlx.img, 0, 0);
	return (0);
}
