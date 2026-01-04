/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collecting_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 20:11:50 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/01 16:05:30 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	get_start_end_len(char *path, int *start, int *end, int *len)
{
	if (!path)
		return (0);
	*start = 0;
	while (path[*start] == ' ' || path[*start] == '\t')
		(*start)++;
	*end = ft_strlen(path) - 1;
	while (*end >= *start && (path[*end] == '\n' || path[*end] == ' '
			|| path[*end] == '\t' || path[*end] == '\r'))
		(*end)--;
	*len = (*end) - (*start) + 1;
	if (*len <= 0)
		return (0);
	return (1);
}

char	*trim_texture_path(char *path, t_config *cfg)
{
	int		start;
	int		end;
	int		len;
	char	*trimmed;
	int		j;

	if (!get_start_end_len(path, &start, &end, &len))
		return (NULL);
	trimmed = ft_malloc(len + 1, cfg);
	j = 0;
	while (j < len)
	{
		trimmed[j] = path[start + j];
		j++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}

int	ft_getrgbs(char *trimmed, char **rgb, t_config *cfg)
{
	if (ft_strncmp(trimmed, "F ", 2) == 0)
	{
		rgb = get_rgb(trimmed + 2, cfg);
		if (!rgb)
			return (1);
		cfg->floor.r = ft_atoi(rgb[0]);
		cfg->floor.g = ft_atoi(rgb[1]);
		cfg->floor.b = ft_atoi(rgb[2]);
	}
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
	{
		rgb = get_rgb(trimmed + 2, cfg);
		if (!rgb)
			return (1);
		cfg->ceiling.r = ft_atoi(rgb[0]);
		cfg->ceiling.g = ft_atoi(rgb[1]);
		cfg->ceiling.b = ft_atoi(rgb[2]);
	}
	return (0);
}

int	ft_gettex_path(char *trimmed, t_config *cfg)
{
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
	{
		cfg->textures.no = trim_texture_path(trimmed + 3, cfg);
		if (!cfg->textures.no)
			return (1);
	}
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
	{
		cfg->textures.so = trim_texture_path(trimmed + 3, cfg);
		if (!cfg->textures.so)
			return (1);
	}
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
	{
		cfg->textures.we = trim_texture_path(trimmed + 3, cfg);
		if (!cfg->textures.we)
			return (1);
	}
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
	{
		cfg->textures.ea = trim_texture_path(trimmed + 3, cfg);
		if (!cfg->textures.ea)
			return (1);
	}
	return (0);
}

int	collecttextures(t_config *cfg, char *line, int j)
{
	char	*trimmed;
	char	**rgb;

	trimmed = line + j;
	rgb = NULL;
	if ((ft_strncmp(trimmed, "NO ", 3) == 0)
		|| (ft_strncmp(trimmed, "SO ", 3) == 0)
		|| (ft_strncmp(trimmed, "WE ", 3) == 0)
		|| (ft_strncmp(trimmed, "EA ", 3) == 0))
	{
		if (ft_gettex_path(trimmed, cfg))
			return (1);
	}
	else if ((ft_strncmp(trimmed, "F ", 2) == 0)
		|| (ft_strncmp(trimmed, "C ", 2) == 0))
	{
		if (ft_getrgbs(trimmed, rgb, cfg))
			return (1);
	}
	else
		return (1);
	return (0);
}
