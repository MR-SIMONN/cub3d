#include "../cub3d.h"

int	handle_close(t_config *cfg)
{
	printf ("everything got freed and deastroyed\n\n");
	destroy_mlx(cfg);
	free_everything(cfg->garbage, 0);
	exit(0);
	return (0);
}

int	handle_key_press(int keycode, t_config *cfg)
{
	printf ("handle keypreess got called\n\n");
	if (keycode == ESC_KEY)
	{
		destroy_mlx(cfg);
		free_everything(g_c(0, 0), 0);
		exit(0);
	}
	else if (keycode == W_KEY)
		cfg->key.w = 1;
	else if (keycode == S_KEY)
		cfg->key.s = 1;
	else if (keycode == D_KEY)
		cfg->key.d = 1;
	else if (keycode == A_KEY)
		cfg->key.a = 1;
	else if (keycode == LEFT_ARROW)
		cfg->key.left = 1;
	else if (keycode == RIGHT_ARROW)
		cfg->key.right = 1;
	return (0);
}

int	handle_key_release(int keycode, t_config *cfg)
{
	printf ("handle key releass got called\n\n");
	if (keycode == W_KEY)
		cfg->key.w = 0;
	else if (keycode == S_KEY)
		cfg->key.s = 0;
	else if (keycode == D_KEY)
		cfg->key.d = 0;
	else if (keycode == A_KEY)
		cfg->key.a = 0;
	else if (keycode == LEFT_ARROW)
		cfg->key.left = 0;
	else if (keycode == RIGHT_ARROW)
		cfg->key.right = 0;
	return (0);
}

