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

// Calculate which pixel from texture to draw based on wall height and position
int	load_pixel_from_texture(t_config *cfg, t_ray *ray, int y, int wall_height)
{
	t_texture_img	*tex;
	double			wall_x;
	int				tex_x;
	int				tex_y;

	// Select the correct texture based on which wall side was hit
	if (ray->side == 0)  // vertical wall (NS facing)
	{
		if (ray->step_x > 0)
			tex = &cfg->tex_ea;  // east wall
		else
			tex = &cfg->tex_we;  // west wall
		// Calculate exact hit position on the wall
		wall_x = cfg->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else  // horizontal wall (EW facing)
	{
		if (ray->step_y > 0)
			tex = &cfg->tex_so;  // south wall
		else
			tex = &cfg->tex_no;  // north wall
		// Calculate exact hit position on the wall
		wall_x = cfg->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	}

	// Convert to texture coordinate (0.0 to 1.0)
	wall_x = wall_x / 64.0;  // Divide by tile size
	wall_x = wall_x - floor(wall_x);  // Get fractional part
	
	// Get the x coordinate on the texture
	tex_x = (int)(wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;

	// Get the y coordinate on the texture based on the screen pixel
	draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
	// Calculate texture position - this accounts for the off-screen portion
	tex_pos = (y - draw_start) * (double)tex->height / wall_height;
	tex_y = (int)tex_pos;

	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;

	return (get_texture_pixel(tex, tex_x, tex_y));
}
