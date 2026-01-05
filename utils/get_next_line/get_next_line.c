/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:12:30 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/05 16:44:05 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	*ft_read(int fd, char *buffer, char *storage)
{
	ssize_t	bytes;
	char	*temp;

	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		if (storage)
			temp = ft_strjoin(storage, buffer);
		else
			temp = ft_strdup(buffer);
		free(storage);
		storage = temp;
		if (ft_strchr(storage, '\n'))
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
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
	int		len;
	char	*line;

	len = 0;
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
	int		len;
	char	*new_storage;

	len = 0;
	while (storage[len] && storage[len] != '\n')
		len++;
	if (storage[len] == '\0')
	{
		free(storage);
		return (NULL);
	}
	new_storage = ft_strdup(storage + len + 1);
	free(storage);
	if (!*new_storage)
	{
		free(new_storage);
		return (NULL);
	}
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
