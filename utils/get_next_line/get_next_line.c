/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:12:30 by ielouarr          #+#    #+#             */
/*   Updated: 2025/11/25 12:20:11 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	*ft_read(int fd, char *buffer, char *storage)
{
	ssize_t	bytes;
	char	*temp;

	while ((bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes] = '\0';
		temp = storage ? ft_strjoin(storage, buffer) : ft_strdup(buffer);
		free(storage);
		storage = temp;
		if (ft_strchr(storage, '\n'))
			break ;
	}
	if (bytes < 0)
	{
		free(storage);
		return (NULL);
	}
	return (storage);
}

static char	*ft_get_line(char *storage)
{
	int		len = 0;
	char	*line;

	if (!storage || !*storage)
		return (NULL);
	while (storage[len] && storage[len] != '\n')
		len++;
	if (storage[len] == '\n')
		len++;
	line = ft_substr(storage, 0, len);
	return (line);
}

static char	*ft_update_storage(char *storage)
{
	int		len = 0;
	char	*new_storage;

	while (storage[len] && storage[len] != '\n')
		len++;
	if (storage[len] == '\0')
		return (free(storage), NULL);
	new_storage = ft_strdup(storage + len + 1);
	free(storage);
	if (!*new_storage)
		return (free(new_storage), NULL);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	storage = ft_read(fd, buffer, storage);
	free(buffer);
	if (!storage)
		return (NULL);
	line = ft_get_line(storage);
	storage = ft_update_storage(storage);
	return (line);
}
