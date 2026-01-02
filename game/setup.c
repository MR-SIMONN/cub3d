/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 10:09:55 by moel-hai          #+#    #+#             */
/*   Updated: 2026/01/01 10:09:55 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_player_vectors(t_config *cfg)
{
	if (!cfg)
		return ;
	if (cfg->player.dir == 'N')
	{
		cfg->player.dir_y = -1.0;
		cfg->player.plane_x = FOV;
	}
	else if (cfg->player.dir == 'S')
	{
		cfg->player.dir_y = 1.0;
		cfg->player.plane_x = -FOV;
	}
	else if (cfg->player.dir == 'E')
	{
		cfg->player.dir_x = 1.0;
		cfg->player.plane_y = FOV;
	}
	else if (cfg->player.dir == 'W')
	{
		cfg->player.dir_x = -1.0;
		cfg->player.plane_y = -FOV;
	}
}

int	init_mlx(t_config *cfg)
{
	cfg->mlx.mlx = mlx_init();
	if (!cfg->mlx.mlx)
		return (1);
	cfg->mlx.win = mlx_new_window(cfg->mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!cfg->mlx.win)
		return (1);
	cfg->mlx.img = mlx_new_image(cfg->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cfg->mlx.img)
		return (1);
	cfg->mlx.addr = mlx_get_data_addr(cfg->mlx.img,
			&cfg->mlx.bpp, &cfg->mlx.line_len, &cfg->mlx.endian);
	if (!cfg->mlx.addr)
		return (1);
	return (0);
}

void	init_ray_data(t_config *cfg, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = cfg->player.dir_x + cfg->player.plane_x * camera_x;
	ray->ray_dir_y = cfg->player.dir_y + cfg->player.plane_y * camera_x;
	ray->map_x = (int)(cfg->player.x / 64);
	ray->map_y = (int)(cfg->player.y / 64);
	ray->delta_dist_x = fabs(64 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(64 / ray->ray_dir_y);
}

void	init_step_sidedist(t_config *cfg, t_ray *ray)
{
	ray->hit = 0;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cfg->player.x - ray->map_x * 64)
			* ray->delta_dist_x / 64;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x * 64 + 64 - cfg->player.x)
			* ray->delta_dist_x / 64;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cfg->player.y - ray->map_y * 64)
			* ray->delta_dist_y / 64;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y * 64 + 64 - cfg->player.y)
			* ray->delta_dist_y / 64;
	}
}
