/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 19:55:55 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/06 16:34:51 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_neighbor(char **map, int i, int j)
{
	if (i < 0 || j < 0 || !map[i])
		return (1);
	if (j >= ft_strlen(map[i]))
		return (1);
	if (map[i][j] == ' ')
		return (1);
	return (0);
}

int	isvalidmap_helper(char **map, int i, int j)
{
	if (map[i][j] == '0')
	{
		if (check_neighbor(map, i - 1, j) || check_neighbor(map, i + 1, j)
			|| check_neighbor(map, i, j - 1) || check_neighbor(map, i, j + 1))
			return (1);
	}
	if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E'
		|| map[i][j] == 'S')
	{
		if (check_neighbor(map, i - 1, j) || check_neighbor(map, i + 1, j)
			|| check_neighbor(map, i, j - 1) || check_neighbor(map, i, j + 1))
			return (1);
	}
	return (0);
}

int	isvalidmap(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == 32)
			j++;
		while (map[i][j])
		{
			if (isvalidmap_helper(map, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	regularmapcheck(char **map, int *i, int *player_counter)
{
	int	j;

	j = 0;
	while (map[*i][j] == 32)
		j++;
	while (map[*i][j])
	{
		if (map[*i][j] != 'N' && map[*i][j] != 'S' && map[*i][j] != 'W'
			&& map[*i][j] != 'E' && map[*i][j] != '0' && map[*i][j] != '1'
			&& map[*i][j] != ' ')
			return (1);
		if (map[*i][j] == 'N' || map[*i][j] == 'S' || map[*i][j] == 'W'
			|| map[*i][j] == 'E')
			(*player_counter)++;
		j++;
	}
	return (0);
}

int	checkmap(char **map)
{
	int	i;
	int	player_counter;

	i = 0;
	player_counter = 0;
	while (map[i])
	{
		if (regularmapcheck(map, &i, &player_counter))
			return (1);
		i++;
	}
	if (player_counter != 1)
		return (1);
	if (isvalidmap(map))
		return (1);
	return (0);
}
