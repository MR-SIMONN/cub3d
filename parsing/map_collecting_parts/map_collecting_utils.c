/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collecting_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:39:49 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/12 22:04:09 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_coma(char *line, int *i, int component)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	if (component < 2)
	{
		if (line[*i] != ',')
			return (0);
		(*i)++;
	}
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	return (1);
}

void	subone(int *component, char *rgbline, int *i)
{
	*i = 0;
	*component = 0;
	while (rgbline[*i] == 32 || rgbline[*i] == 9)
		(*i)++;
}

int	regularget(char *lrgb, int *i, int *component, char **rgb)
{
	int	count;
	int	start;

	while ((*component) < 3)
	{
		count = 0;
		if (lrgb[*i] < '0' || lrgb[*i] > '9')
			return (0);
		while (lrgb[*i] == '0' && lrgb[*i + 1] >= '0' && lrgb[*i + 1] <= '9')
			(*i)++;
		start = *i;
		while (lrgb[*i] >= '0' && lrgb[*i] <= '9')
		{
			count++;
			(*i)++;
		}
		if (count == 0 || count > 3)
			return (0);
		if (!check_coma(lrgb, i, *component))
			return (0);
		rgb[*component] = ft_substr(lrgb, start, 3);
		(*component)++;
	}
	return (1);
}

char	**get_rgb(char *rgbline, t_config *cfg)
{
	int		i;
	int		component;
	char	**rgb;

	subone(&component, rgbline, &i);
	rgb = ft_malloc(sizeof(char *) * 4, cfg);
	if (!regularget(rgbline, &i, &component, rgb))
		return (NULL);
	rgb[component] = NULL;
	return (rgb);
}
