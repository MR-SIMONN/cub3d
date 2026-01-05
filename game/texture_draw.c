/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:19:42 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/05 22:27:09 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	calculate_line_height(t_ray *ray)
{
	return ((int)(WIN_HEIGHT / (ray->perp_wall_dist / 64)));
}

void	calculate_draw_bounds(int line_height, int *draw_start,
		int *draw_end)
{
	*draw_start = WIN_HEIGHT / 2 - line_height / 2;
	*draw_end = WIN_HEIGHT / 2 + line_height / 2;
}

void	adjust_draw_bounds(int *draw_start, int *draw_end,
		double *tex_pos, double step)
{
	if (*draw_start < 0)
	{
		*tex_pos = -(*draw_start) * step;
		*draw_start = 0;
	}
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}

void	draw_wall_column(t_config *cfg, t_texture_img *tex,
		int tex_x, t_draw_params *params)
{
	int		y;
	int		tex_y;

	y = params->draw_start;
	while (y <= params->draw_end)
	{
		tex_y = (int)params->tex_pos;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		put_pixel_to_img(&cfg->mlx, params->x, y,
			get_texture_pixel(tex, tex_x, tex_y));
		params->tex_pos += params->step;
		y++;
	}
}

void	draw_textured_wall(t_config *cfg, t_ray *ray, int x)
{
	t_texture_img	*tex;
	int				line_height;
	t_draw_params	params;
	int				tex_x;

	params.x = x;
	tex = select_texture(cfg, ray);
	line_height = calculate_line_height(ray);
	calculate_draw_bounds(line_height, &params.draw_start, &params.draw_end);
	tex_x = (int)(calculate_wall_x(cfg, ray) * (double)tex->width);
	params.step = (double)tex->height / line_height;
	params.tex_pos = 0;
	adjust_draw_bounds(&params.draw_start, &params.draw_end,
		&params.tex_pos, params.step);
	draw_wall_column(cfg, tex, tex_x, &params);
}
