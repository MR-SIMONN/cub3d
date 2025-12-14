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