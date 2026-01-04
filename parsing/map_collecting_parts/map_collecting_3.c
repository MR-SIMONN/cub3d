/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collecting_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 20:15:04 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/01 20:34:25 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	ft_init(int *count, int *capacity)
{
	*count = 0;
	*capacity = 10;
}

int	sc_init(char ***map_extract, int *capacity, int count, t_config *cfg)
{
	*capacity *= 2;
	*map_extract = realloc_map(*map_extract, count, *capacity, cfg);
	if (!*map_extract)
		return (1);
	return (0);
}

char	**collectmap(char *line, int fd, t_config *cfg)
{
	char	**map_extract;
	int		count;
	int		capacity;

	ft_init(&count, &capacity);
	map_extract = ft_malloc(sizeof(char *) * (capacity + 1), cfg);
	map_extract[count++] = remove_backslash_n(line, cfg);
	line = get_next_line(fd);
	while (line)
	{
		if (count >= capacity)
		{
			if (sc_init(&map_extract, &capacity, count, cfg))
				return (NULL);
		}
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			break ;
		}
		map_extract[count++] = remove_backslash_n(line, cfg);
		line = get_next_line(fd);
	}
	map_extract[count] = NULL;
	return (map_extract);
}
