/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 17:30:00 by ielouarr          #+#    #+#             */
/*   Updated: 2025/11/25 13:12:32 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


void init_config(t_config *config)
{
    if (!config)
        return;
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
    config->garbage = NULL;
}