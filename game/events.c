#include "../cub3d.h"

int	handle_close(t_config *cfg)
{
	free_everything(g_c(0, 0), 0);
    return (0);
}

int	handle_key_press(int keycode, t_config *cfg)
{
	if (keycode == ESC_KEY)
		free_everything(g_c(0, 0), 0);
    else if (keycode == W_KEY)
		move_player(cfg, cfg->player.dir_x, cfg->player.dir_y);
	else if (keycode == S_KEY)
		move_player(cfg, -cfg->player.dir_x, -cfg->player.dir_y);
	else if (keycode == D_KEY)
		move_player(cfg, cfg->player.plane_x, cfg->player.plane_y);
	else if (keycode == A_KEY)
		move_player(cfg, -cfg->player.plane_x, -cfg->player.plane_y);
	else if (keycode == LEFT_ARROW)
		rotate_player(cfg, 0.05);
	else if (keycode == RIGHT_ARROW)
		rotate_player(cfg, -0.05);
	
	if (keycode == W_KEY || keycode == S_KEY || keycode == A_KEY
		|| keycode == D_KEY || keycode == LEFT_ARROW || keycode == RIGHT_ARROW)
		render_frame(cfg);
	
	return (0);
}