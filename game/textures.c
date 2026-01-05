/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 10:09:58 by moel-hai          #+#    #+#             */
/*   Updated: 2026/01/05 20:34:51 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	load_texture(char *path, t_texture_img *tex, void *mlx)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
		return (1);
	return (0);
}

int	load_all_textures(t_config *cfg)
{
	if (load_texture(cfg->textures.no, &cfg->tex_no, cfg->mlx.mlx))
		return (printf("Error: Failed to load NO texture\n"), 1);
	if (load_texture(cfg->textures.so, &cfg->tex_so, cfg->mlx.mlx))
		return (printf("Error: Failed to load SO texture\n"), 1);
	if (load_texture(cfg->textures.we, &cfg->tex_we, cfg->mlx.mlx))
		return (printf("Error: Failed to load WE texture\n"), 1);
	if (load_texture(cfg->textures.ea, &cfg->tex_ea, cfg->mlx.mlx))
		return (printf("Error: Failed to load EA texture\n"), 1);
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

void	draw_textured_wall(t_config *cfg, t_ray *ray, int x)
{
	t_texture_img	*tex;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				y;

	tex = select_texture(cfg, ray);
	line_height = (int)(WIN_HEIGHT / (ray->perp_wall_dist / 64));

	draw_start = WIN_HEIGHT / 2 - line_height / 2;
	draw_end = WIN_HEIGHT / 2 + line_height / 2;

	tex_x = (int)(calculate_wall_x(cfg, ray) * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	
	step = (double)tex->height / line_height;
	tex_pos = 0;

	if (draw_start < 0)
	{
		tex_pos = -draw_start * step;
		draw_start = 0;
	}
	
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	
	y = draw_start;
	while (y <= draw_end)
	{
		int tex_y = (int)tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		
		put_pixel_to_img(&cfg->mlx, x, y, get_texture_pixel(tex, tex_x, tex_y));
		tex_pos += step;
		y++;
	}
}
