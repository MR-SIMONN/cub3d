/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 10:09:28 by moel-hai          #+#    #+#             */
/*   Updated: 2026/01/01 10:09:28 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	get_texture_pixel(t_texture_img *tex, int x, int y)
{
	char	*dst;
	int		offset;
	int		bytes_per_pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	bytes_per_pixel = tex->bpp / 8;
	offset = (y * tex->line_len) + (x * bytes_per_pixel);
	dst = tex->addr + offset;
	return (*(unsigned int *)dst);
}
