/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:30:00 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/06 15:54:37 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_config	*configs(int should_update,	t_config *new_value)
{
	static t_config	*h;

	if (should_update)
		h = new_value;
	return (h);
}

void	init_more(t_config *cfg)
{
	cfg->mlx.mlx = NULL;
	cfg->mlx.win = NULL;
	cfg->mlx.img = NULL;
	cfg->mlx.addr = NULL;
	cfg->tex_no.img = NULL;
	cfg->tex_so.img = NULL;
	cfg->tex_we.img = NULL;
	cfg->tex_ea.img = NULL;
	cfg->tex_no.addr = NULL;
	cfg->tex_so.addr = NULL;
	cfg->tex_we.addr = NULL;
	cfg->tex_ea.addr = NULL;
}

void	init_config(t_config *config)
{
	if (!config)
		return ;
	config->textures.no = NULL;
	config->textures.so = NULL;
	config->textures.we = NULL;
	config->textures.ea = NULL;
	config->floor.r = 0;
	config->floor.g = 0;
	config->floor.b = 0;
	config->ceiling.r = 0;
	config->ceiling.g = 0;
	config->ceiling.b = 0;
	config->map.grid = NULL;
	config->map.width = 0;
	config->map.height = 0;
	config->player.x = 0;
	config->player.y = 0;
	config->player.dir = 0;
	config->player.dir_x = 0;
	config->player.dir_y = 0;
	config->player.plane_x = 0;
	config->player.plane_y = 0;
	config->garbage = NULL;
	init_more(config);
	configs(1, config);
}
