#include "../../cub3d.h"

void	destroy_texture(t_texture_img *tex, void *mlx)
{
	if (tex && tex->img)
	{
		mlx_destroy_image(mlx, tex->img);
		tex->img = NULL;
		tex->addr = NULL;
	}
}

void	destroy_all_textures(t_config *cfg)
{
	if (!cfg->mlx.mlx)
		return ;
	destroy_texture(&cfg->tex_no, cfg->mlx.mlx);
	destroy_texture(&cfg->tex_so, cfg->mlx.mlx);
	destroy_texture(&cfg->tex_we, cfg->mlx.mlx);
	destroy_texture(&cfg->tex_ea, cfg->mlx.mlx);
}

void	destroy_mlx(t_config *cfg)
{
	if (!cfg->mlx.mlx)
		return ;
	destroy_all_textures(cfg);
	if (cfg->mlx.img)
	{
		mlx_destroy_image(cfg->mlx.mlx, cfg->mlx.img);
		cfg->mlx.img = NULL;
	}
	if (cfg->mlx.win)
	{
		mlx_destroy_window(cfg->mlx.mlx, cfg->mlx.win);
		cfg->mlx.win = NULL;
	}
}
