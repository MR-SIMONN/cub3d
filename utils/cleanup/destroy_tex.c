#include "../../cub3d.h"

// Destroy a single texture image
void	destroy_texture(t_texture_img *tex, void *mlx)
{
	if (tex && tex->img)
	{
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
		tex->addr = NULL;
	}
}

// Destroy all loaded textures
void	destroy_all_textures(t_config *cfg)
{
	if (!cfg->mlx.mlx)
		return;
	
	destroy_texture(&cfg->tex_no, cfg->mlx.mlx);
	destroy_texture(&cfg->tex_so, cfg->mlx.mlx);
	destroy_texture(&cfg->tex_we, cfg->mlx.mlx);
	destroy_texture(&cfg->tex_ea, cfg->mlx.mlx);
}

// Complete MLX cleanup function
void	destroy_mlx(t_config *cfg)
{
	if (!cfg->mlx.mlx)
		return;
	
	// Destroy textures first
	destroy_all_textures(cfg);
	
	// Destroy the main image buffer
	if (cfg->mlx.img)
	{
		mlx_destroy_image(cfg->mlx.mlx, cfg->mlx.img);
		cfg->mlx.img = NULL;
	}
	
	// Destroy window
	if (cfg->mlx.win)
	{
		mlx_destroy_window(cfg->mlx.mlx, cfg->mlx.win);
		cfg->mlx.win = NULL;
	}
	
	// Note: On macOS, don't destroy mlx pointer as it causes issues
	// On Linux, you might need to free it differently
	// cfg->mlx.mlx = NULL;
}