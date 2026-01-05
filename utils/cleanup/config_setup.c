/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mihowk <mihowk@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:30:00 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/04 22:14:12 by mihowk           ###   ########.fr       */
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
	configs(1, config);
}
