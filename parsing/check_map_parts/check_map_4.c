/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 19:59:09 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/01 16:05:08 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	**realloc_map(char **map, int old_size, int new_size, t_config *cfg)
{
	char	**new_map;
	int		i;

	new_map = ft_malloc(sizeof(char *) * (new_size + 1), cfg);
	i = 0;
	while (i < old_size && map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	return (new_map);
}

char	*remove_backslash_n(char *line, t_config *cfg)
{
	int		i;
	char	*new_line;
	int		j;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	new_line = ft_malloc(i + 1, cfg);
	j = 0;
	while (j < i)
	{
		new_line[j] = line[j];
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

char	**mapextracting(char *line, int fd, t_config *cfg)
{
	int		capacity;
	int		count;
	char	**map_extract;

	map_extract = NULL;
	capacity = 10;
	count = 0;
	map_extract = ft_malloc(sizeof(char *) * (capacity + 1), cfg);
	map_extract[count++] = remove_backslash_n(line, cfg);
	line = get_next_line(fd);
	while (line)
	{
		if (count >= capacity)
		{
			capacity *= 2;
			map_extract = realloc_map(map_extract, count, capacity, cfg);
		}
		if (line[0] == '\n' || line[0] == '\0')
			return (NULL);
		map_extract[count++] = remove_backslash_n(line, cfg);
		line = get_next_line(fd);
	}
	map_extract[count] = NULL;
	return (map_extract);
}

void	ft_increment(int *tex_total, int *dup, int i)
{
	dup[i]++;
	(*tex_total)++;
}

int	count_tex(char *line, int *tex_total, int *dup)
{
	if ((ft_strncmp(line, "NO ", 3) == 0) && check_texture_filename(line))
		ft_increment(tex_total, dup, 0);
	else if ((ft_strncmp(line, "SO ", 3) == 0) && check_texture_filename(line))
		ft_increment(tex_total, dup, 1);
	else if ((ft_strncmp(line, "WE ", 3) == 0) && check_texture_filename(line))
		ft_increment(tex_total, dup, 2);
	else if ((ft_strncmp(line, "EA ", 3) == 0) && check_texture_filename(line))
		ft_increment(tex_total, dup, 3);
	else if ((ft_strncmp(line, "F ", 2) == 0) && check_rgb(line))
		ft_increment(tex_total, dup, 4);
	else if ((ft_strncmp(line, "C ", 2) == 0) && check_rgb(line))
		ft_increment(tex_total, dup, 5);
	else
		return (0);
	return (1);
}
