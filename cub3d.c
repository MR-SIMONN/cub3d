/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:30:21 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/06 16:53:05 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	gettofilename(char *line, int *i, int *j)
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

int	check_cub3d_filename(char *line)
{
	int	i;
	int	j;
	int	fname_len;

	if (!gettofilename(line, &i, &j))
		return (0);
	fname_len = j - i;
	if (fname_len < 4)
		return (0);
	if (!(line[i + fname_len - 4] == '.'
			&& line[i + fname_len - 3] == 'c'
			&& line[i + fname_len - 2] == 'u'
			&& line[i + fname_len - 1] == 'b'))
		return (0);
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] != '\0' && line[j] != '\n')
		return (0);
	return (1);
}

int	parsing(int ac, char **av, t_config *configs)
{
	int	ret;
	int	fd;

	if (ac != 2)
		return (printf("Error\nCub3d : Invalid args [./cub3d your_map]"), 1);
	if (!check_cub3d_filename(av[1]))
		return (printf("Error\nCub3d : Wrong map name [your_map`.cub`]"), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCub3d : can't access the file map"), 1);
	close(fd);
	init_config(configs);
	if (check_validmap(av[1], configs))
		return (printf("Error\nCub3d : invalid map"),
			free_everything(g_c(0, 0), -1, 0), 1);
	ret = mapcollecting(configs, av[1]);
	if (ret)
	{
		free_everything(g_c(0, 0), -1, 0);
		return (printf("Error\nCub3d : invalid map"), 1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_config	configs;

	if (parsing(ac, av, &configs))
		return (1);
	run_game(&configs);
	return (0);
}
