/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 10:09:34 by moel-hai          #+#    #+#             */
/*   Updated: 2026/01/01 10:09:34 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_close(t_config *cfg)
{
	free_everything(cfg->garbage, 0);
	return (0);
}

int	handle_key_press(int keycode, t_config *cfg)
{
	if (keycode == ESC_KEY)
		free_everything(g_c(0, 0), 0);
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
