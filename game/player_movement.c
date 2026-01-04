/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 10:09:48 by moel-hai          #+#    #+#             */
/*   Updated: 2026/01/01 10:09:48 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_player(t_config *cfg, double dir_x, double dir_y)
{
	double	new_x;
	double	new_y;

	new_x = cfg->player.x + dir_x * PLAYER_SPEED;
	new_y = cfg->player.y + dir_y * PLAYER_SPEED;
	if (cfg->map.grid[(int)(new_y / 64)][(int)(cfg->player.x / 64)] != '1')
		cfg->player.y = new_y;
	if (cfg->map.grid[(int)(cfg->player.y / 64)][(int)(new_x / 64)] != '1')
		cfg->player.x = new_x;
}

void	rotate_player(t_config *cfg, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cfg->player.dir_x;
	cfg->player.dir_x = cfg->player.dir_x * cos(rot_speed)
		- cfg->player.dir_y * sin(rot_speed);
	cfg->player.dir_y = old_dir_x * sin(rot_speed)
		+ cfg->player.dir_y * cos(rot_speed);
	old_plane_x = cfg->player.plane_x;
	cfg->player.plane_x = cfg->player.plane_x * cos(rot_speed)
		- cfg->player.plane_y * sin(rot_speed);
	cfg->player.plane_y = old_plane_x * sin(rot_speed)
		+ cfg->player.plane_y * cos(rot_speed);
}

int	keys_update(t_config *cfg)
{
	if (cfg->key.w)
		move_player(cfg, cfg->player.dir_x, cfg->player.dir_y);
	if (cfg->key.d)
		move_player(cfg, cfg->player.plane_x, cfg->player.plane_y);
	if (cfg->key.s)
		move_player(cfg, -cfg->player.dir_x, -cfg->player.dir_y);
	if (cfg->key.a)
		move_player(cfg, -cfg->player.plane_x, -cfg->player.plane_y);
	if (cfg->key.left)
		rotate_player(cfg, -ROTATION_SPEED);
	if (cfg->key.right)
		rotate_player(cfg, ROTATION_SPEED);
	return (0);
}
