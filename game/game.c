
#include "../cub3d.h"

int	run_game(t_config *configs)
{
    init_player_vectors(configs);
    if (init_mlx(configs))
        free_everything(g_c(0, 0), 1)
    mlx_hook(configs->mlx.win, 2, 1L<<0, handle_key_press, configs);
	mlx_hook(configs->mlx.win, 17, 1L<<17, handle_close, configs);
    mlx_loop_hook(configs->mlx.mlx, render_frame, configs);
	mlx_loop(configs->mlx.mlx);

	mlx_put_image_to_window(cfg->mlx.mlx, cfg->mlx.win, cfg->mlx.img, 0, 0);

    return (0);
}