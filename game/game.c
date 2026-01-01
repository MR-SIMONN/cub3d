#include "../cub3d.h"

int	run_game(t_config *configs)
{
	init_player_vectors(configs);
	if (init_mlx(configs))
		free_everything(g_c(0, 0), 1);
	if (load_all_textures(configs))
	{
		printf("Error: Failed to load textures\n");
		free_everything(g_c(0, 0), 1);
	}
	mlx_hook (configs->mlx.win, 2, 1, handle_key_press, configs);
	mlx_hook (configs->mlx.win, 17, 1<<17, handle_close, configs);
	mlx_loop_hook (configs->mlx.mlx, render_frame, configs);
	mlx_loop (configs->mlx.mlx);
	return (0);
}
