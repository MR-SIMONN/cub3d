/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 19:57:33 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/01 20:17:36 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	fast_check(int tex_total, int dup[])
{
	int	i;

	if (tex_total != 6)
		return (0);
	i = 0;
	while (i < 6)
	{
		if (dup[i] != 1)
			return (0);
		i++;
	}
	return (1);
}

static int	read_texture_lines(t_tex_par *ctx)
{
	char	*line;
	int		ret;

	line = get_next_line(ctx->fd);
	while (line)
	{
		ret = handle_line(line, ctx);
		free(line);
		if (ret == 0)
		{
			line = get_next_line(ctx->fd);
			continue ;
		}
		if (ret == -1)
			return (-1);
		if (ret == 1)
			return (1);
		line = get_next_line(ctx->fd);
	}
	return (0);
}

int	ft_initit(char *map, int *dup, int *fd, int *tex_total)
{
	int	i;

	*fd = open(map, O_RDONLY);
	*tex_total = 0;
	i = 0;
	while (i < 6)
	{
		dup[i] = 0;
		i++;
	}
	return (*fd);
}

static int	init_tex_ctx(t_tex_par *ctx, char *map, t_config *cfg)
{
	ctx->map_extract = NULL;
	ctx->cfg = cfg;
	if (ft_initit(map, ctx->dup, &ctx->fd, &ctx->tex_total) < 0)
	{
		printf("have problem in fd of map check\n");
		return (-1);
	}
	return (0);
}

char	**check_textures(char *map, t_config *cfg)
{
	t_tex_par	ctx;
	int			ret;

	if (init_tex_ctx(&ctx, map, cfg) < 0)
		return (NULL);
	ret = read_texture_lines(&ctx);
	close(ctx.fd);
	if (ret == -1)
		return (NULL);
	if (!fast_check(ctx.tex_total, ctx.dup))
		return (NULL);
	return (ctx.map_extract);
}
