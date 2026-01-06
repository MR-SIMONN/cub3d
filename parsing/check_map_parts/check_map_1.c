/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:42:26 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/06 16:52:27 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	gettofilenamee(char *line, int *i, int *j)
{
	if (!line)
		return (0);
	*i = 2;
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	if (!line[*i] || line[*i] == '\n')
		return (0);
	*j = *i;
	while (line[*j] && line[*j] != '\n')
		(*j)++;
	while (*j > *i && (line[*j - 1] == ' ' || line[*j - 1] == '\t'))
		(*j)--;
	return (1);
}

int	check_texture_filename(char *line)
{
	int	i;
	int	j;
	int	fname_len;

	if (!gettofilenamee(line, &i, &j))
		return (0);
	fname_len = j - i;
	if (fname_len < 4)
		return (0);
	if (!(line[i + fname_len - 4] == '.'
			&& line[i + fname_len - 3] == 'x'
			&& line[i + fname_len - 2] == 'p'
			&& line[i + fname_len - 1] == 'm'))
		return (0);
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] != '\0' && line[j] != '\n')
		return (0);
	return (1);
}

int	check_validmap(char *mapfile_name, t_config *cfg)
{
	char	**map;

	map = check_textures(mapfile_name, cfg);
	if (!map)
		return (1);
	if (checkmap(map))
		return (1);
	return (0);
}
