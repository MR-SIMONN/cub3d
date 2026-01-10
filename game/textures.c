/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 10:09:58 by moel-hai          #+#    #+#             */
/*   Updated: 2026/01/10 20:56:08 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_texture(char *path, t_texture_img *tex, void *mlx)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (1);
	return (0);
}

int	load_all_textures(t_config *cfg)
{
	if (load_texture(cfg->textures.no, &cfg->tex_no, cfg->mlx.mlx))
		return (printf("Error\nFailed to load NO texture\n"), 1);
	if (load_texture(cfg->textures.so, &cfg->tex_so, cfg->mlx.mlx))
		return (printf("Error\nFailed to load SO texture\n"), 1);
	if (load_texture(cfg->textures.we, &cfg->tex_we, cfg->mlx.mlx))
		return (printf("Error\nFailed to load WE texture\n"), 1);
	if (load_texture(cfg->textures.ea, &cfg->tex_ea, cfg->mlx.mlx))
		return (printf("Error\nFailed to load EA texture\n"), 1);
	return (0);
}

t_texture_img	*select_texture(t_config *cfg, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (&cfg->tex_ea);
		else
			return (&cfg->tex_we);
	}
	else
	{
		if (ray->step_y > 0)
			return (&cfg->tex_so);
		else
			return (&cfg->tex_no);
	}
}

double	calculate_wall_x(t_config *cfg, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = cfg->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = cfg->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x = wall_x / 64;
	wall_x = wall_x - floor(wall_x);
	return (wall_x);
}
