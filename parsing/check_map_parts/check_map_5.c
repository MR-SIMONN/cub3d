/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 20:05:03 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/12 17:30:08 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	super_check(char *line, int *j)
{
	while (line[*j] == 32 || (line[*j] >= 9 && line[*j] <= 13))
		(*j)++;
	if (!line[*j] || line[*j] == '\n')
		return (0);
	return (1);
}

int	handle_line(char *line, t_tex_par *ctx)
{
	int	j;

	j = 0;
	if (!super_check(line, &j))
		return (0);
	if (line[j] == '1')
	{
		ctx->map_extract = mapextracting(line, ctx->fd, ctx->cfg);
		if (!ctx->map_extract)
			return (-1);
		return (1);
	}
	if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E'
		|| line[j] == 'W' || line[j] == 'F' || line[j] == 'C')
	{
		if (!count_tex(line + j, &ctx->tex_total, ctx->dup))
			return (-1);
		return (0);
	}
	if (line[j] != '\n')
		return (-1);
	return (0);
}

int	check_comma(char *line, int *i, int *component)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if ((*component) < 2)
	{
		if (line[*i] != ',')
			return (0);
		(*i)++;
	}
	return (1);
}

int    regularcheck(char *l, int *i, int *component)
{
	int	count;
	int	start;

	while ((*component) < 3)
	{
		count = 0;
		if (l[*i] < '0' || l[*i] > '9')
			return (0);
		while (l[*i] == '0' && l[*i + 1] >= '0' && l[*i + 1] <= '9')
			(*i)++;
		start = *i;
		while (l[*i] >= '0' && l[*i] <= '9')
		{
			count++;
			(*i)++;
		}
		if (count == 0 || count > 3 || !check_comma(l, i, component))
			return (0);
		if (!checkrange(l, start))
			return (0);
		while (l[*i] == ' ' || l[*i] == '\t')
			(*i)++;
		(*component)++;
	}
	return (1);
}

int	check_rgb(char *line)
{
	int	i;
	int	component;

	if (!line)
		return (0);
	i = 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	component = 0;
	if (!regularcheck(line, &i, &component))
		return (0);
	if (line[i] != '\0' && line[i] != '\n')
		return (0);
	return (1);
}
