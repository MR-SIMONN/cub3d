/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcollecting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:34:18 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/03 20:57:33 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	scollect(t_config *cfg)
{
	int	height;
	int	width;
	int	i;
	int	j;

	height = 0;
	width = 0;
	i = 0;
	while (cfg->map.grid[i])
	{
		j = 0;
		while (cfg->map.grid[i][j])
		{
			if (width < ft_strlen(cfg->map.grid[i]))
				width = ft_strlen(cfg->map.grid[i]);
			j++;
		}
		i++;
	}
	height = i;
	cfg->map.height = height;
	cfg->map.width = width;
	return (0);
}

void	init_xy(int j, int i, double *x, double *y)
{
	*x = j;
	*y = i;
}

int	tcollect(t_config *cfg)
{
	int		i;
	int		j;
	double	x;
	double	y;

	i = 0;
	while (cfg->map.grid[i])
	{
		j = 0;
		while (cfg->map.grid[i][j])
		{
			if (cfg->map.grid[i][j] == 'N' || cfg->map.grid[i][j] == 'S'
				|| cfg->map.grid[i][j] == 'W' || cfg->map.grid[i][j] == 'E')
			{
				init_xy(j, i, &x, &y);
				cfg->player.x = (x + 0.5) * 64;
				cfg->player.y = (y + 0.5) * 64;
				cfg->player.dir = cfg->map.grid[i][j];
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	mapcollecting(t_config *config_list, char *map)
{
	if (fcollect(map, config_list))
		return (1);
	scollect(config_list);
	tcollect(config_list);
	return (0);
}
