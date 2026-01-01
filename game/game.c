#include "../cub3d.h"

int	run_game(t_config *configs)
{
	init_player_vectors(configs);
	init_keys(configs);
	// printf ("keys ---> %d\n", configs->key.a);
	// exit(0);
	if (init_mlx(configs))
		free_everything(g_c(0, 0), 1);
	if (load_all_textures(configs))
	{
		printf("Error: Failed to load textures\n");
		free_everything(g_c(0, 0), 1);
	}
	mlx_loop_hook (configs->mlx.mlx, render_frame, configs);
	mlx_hook (configs->mlx.win, 2, 0, handle_key_press, configs);
	mlx_hook (configs->mlx.win, 3, 0, handle_key_release, configs);
	mlx_hook (configs->mlx.win, 17, 0, handle_close, configs);
	mlx_loop (configs->mlx.mlx);
	return (0);
}
