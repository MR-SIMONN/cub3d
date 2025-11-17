/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcollecting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:34:18 by ielouarr          #+#    #+#             */
/*   Updated: 2025/10/25 18:23:44 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char *trim_texture_path(char *path)
{
    int start;
    int end;
    int len;
    char *trimmed;
    int j;
    
    if (!path)
        return (NULL);
    start = 0;
    while (path[start] == ' ' || path[start] == '\t')
        start++;
    end = ft_strlen(path) - 1;
    while (end >= start && (path[end] == '\n' || path[end] == ' ' || 
           path[end] == '\t' || path[end] == '\r'))
        end--;
    len = end - start + 1;
    
    if (len <= 0)
        return (NULL);
    trimmed = malloc(len + 1);
    if (!trimmed)
        return (NULL);
    j = 0;
    while (j < len)
    {
        trimmed[j] = path[start + j];
        j++;
    }
    trimmed[j] = '\0';
    
    return (trimmed);
}

int collecttextures(t_config *cfg, char *line, int j)
{
    char *trimmed = line + j;
	char **rgb = NULL;
	if ((ft_strncmp(trimmed, "NO ", 3) == 0))
	{
		cfg->textures.no = trim_texture_path(trimmed + 3);
        if (!cfg->textures.no)
            return (1);		
	}
	else if ((ft_strncmp(trimmed, "SO ", 3) == 0))
	{
		cfg->textures.so = trim_texture_path(trimmed + 3);
        if (!cfg->textures.so)
            return (1);		
	}
	else if ((ft_strncmp(trimmed, "WE ", 3) == 0))
	{
		cfg->textures.we = trim_texture_path(trimmed + 3);
        if (!cfg->textures.we)
            return (1);		
	}
	else if ((ft_strncmp(trimmed, "EA ", 3) == 0))
	{
		cfg->textures.ea = trim_texture_path(trimmed + 3);
        if (!cfg->textures.ea)
            return (1);		
	}
	else if ((ft_strncmp(trimmed, "F ", 2) == 0))
	{
		rgb = get_rgb(trimmed + 2);
		if(!rgb)
			return (1);
		cfg->floor.r = ft_atoi(rgb[0]);
        cfg->floor.g = ft_atoi(rgb[1]);
        cfg->floor.b = ft_atoi(rgb[2]);
	}
	else if ((ft_strncmp(trimmed, "C ", 2) == 0))
	{
		rgb = get_rgb(trimmed + 2);
		if(!rgb)
			return (1);
		cfg->ceiling.r = ft_atoi(rgb[0]);
        cfg->ceiling.g = ft_atoi(rgb[1]);
        cfg->ceiling.b = ft_atoi(rgb[2]);
	}
	else
        return (1);
    return (0);
}



char **collectmap(char *line, int fd)
{
	char **map_extract;
	int capacity = 10;
	int count = 0;

	map_extract = malloc(sizeof(char *) * (capacity + 1));
	if (!map_extract)
		return (NULL);
	map_extract[count++] = remove_backslash_n(line);
	while ((line = get_next_line(fd)))
	{
		if (count >= capacity)
		{
			capacity *= 2;
			map_extract = realloc_map(map_extract, count, capacity);
			if (!map_extract)
				return (NULL);
		}
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			break;
		}
				
		map_extract[count++] = remove_backslash_n(line);
	}
	map_extract[count] = NULL;
	return (map_extract);
}


int fcollect(char *mapfile, t_config *cfg)
{
	int fd;
	char *line;
	int j;

	fd = open(mapfile, O_RDONLY);
	if (fd < 0)
		return (printf("Error: cannot open map file\n"), 0);
	while ((line = get_next_line(fd)))
	{
		j = 0;
		while (line[j] == 32 || (line[j] >= 9 && line[j] <= 13))
			j++;
		if (!line[j] || line[j] == '\n')
		{
			free(line);
			continue;
		}
		if (line[j] == '1')
		{
			cfg->map.grid = collectmap(line, fd);
			if(!cfg->map.grid)
				cfg->map.grid = NULL;
			return (0);
		}
		if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E' ||
			line[j] == 'W' || line[j] == 'F' || line[j] == 'C')
		{
			if (collecttextures(cfg, line, j))
				return (free(line), 0);
		}
		else
			return (free(line), 0);
		free(line);
	}
	return (1);
}

int scollect(t_config *cfg)
{
	int height = 0;
	int width = 0;
	int i= 0 ;
	int j = 0;
	while(cfg->map.grid[i])
	{
		j = 0;
		while(cfg->map.grid[i][j])
		{
			if(width < ft_strlen(cfg->map.grid[i]))
				width = ft_strlen(cfg->map.grid[i]);
			j++;	
		}
		i++;
	}
	height = i;
	cfg->map.height = height;
	cfg->map.width = width;
	return 0;
}

int tcollect(t_config *cfg)
{
	int i= 0 ;
	int j = 0;
	double x = 0;
	double y = 0;
	while(cfg->map.grid[i])
	{
		j = 0;
		while(cfg->map.grid[i][j])
		{
			if(cfg->map.grid[i][j] == 'N' || cfg->map.grid[i][j] == 'S' 
				|| cfg->map.grid[i][j] == 'W' || cfg->map.grid[i][j] == 'E')
			{
				x = j;
				y = i;
				cfg->player.x = (x + 0.5) * 64;
				cfg->player.y = (y + 0.5) * 64;
				cfg->player.dir = cfg->map.grid[i][j];
				return 0;
			}
			j++;	
		}
		i++;
	}
	
	return 1;
}
int mapcollecting(t_config *config_list, char *map)
{
	if (fcollect(map, config_list))
		return (1);
	scollect(config_list);
	tcollect(config_list);
	return (0);
}
