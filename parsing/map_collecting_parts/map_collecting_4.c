/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collecting_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:53:53 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/06 16:01:29 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	skipiiii(int *j, char *line)
{
	*j = 0;
	while (line[*j] == 32 || (line[*j] >= 9 && line[*j] <= 13))
		(*j)++;
	if (!line[*j] || line[*j] == '\n')
		return (0);
	return (1);
}

int	is_map_start(char *line, int j)
{
	if (line[j] == '1')
		return (1);
	return (0);
}

int	is_texture_id(char c)
{
	if (c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == 'F' || c == 'C')
		return (1);
	return (0);
}

int	process_line(char *line, int fd, t_config *cfg)
{
	int	j;

	if (!skipiiii(&j, line))
		return (0);
	if (is_map_start(line, j))
	{
		cfg->map.grid = collectmap(line, fd, cfg);
		if (!cfg->map.grid)
			return (1);
		return (2);
	}
	if (is_texture_id(line[j]))
	{
		if (collecttextures(cfg, line, j))
			return (1);
		return (0);
	}
	return (1);
}

int	fcollect(char *mapfile, t_config *cfg)
{
	int		fd;
	char	*line;
	int		ret;

	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		return (printf("Error: cannot open map file\n"), 0);
	line = get_next_line(fd);
	while (line)
	{
		ret = process_line(line, fd, cfg);
		if (ret == 1)
			return (1);
		if (ret == 2)
			return (0);
		line = get_next_line(fd);
	}
	return (1);
}
