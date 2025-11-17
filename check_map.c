/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielouarr <ielouarr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:42:26 by ielouarr          #+#    #+#             */
/*   Updated: 2025/10/15 16:33:02 by ielouarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_texture_filename(char *line)
{
    int i;
    int j;
    int fname_len;

    if (!line)
        return 0;

    if (ft_strlen(line) < 8)
        return 0;

    i = 2;
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (!line[i] || line[i] == '\n')
        return 0;
    j = i;
    while (line[j] && line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
        j++;

    fname_len = j - i;
    if (fname_len < 4)
        return 0;

    if (!(line[i + fname_len - 4] == '.'
          && line[i + fname_len - 3] == 'x'
          && line[i + fname_len - 2] == 'p'
          && line[i + fname_len - 1] == 'm'))
        return 0;

    while (line[j] && (line[j] == ' ' || line[j] == '\t'))
        j++;

    if (line[j] != '\0' && line[j] != '\n')
        return 0;

    return 1;
}

int	check_rgb(char *line)
{
	int	i;
	int	value;
	int	count;
	int	component;

	if (!line)
		return (0);
	i = 2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	component = 0;
	while (component < 3)
	{
		value = 0;
		count = 0;
		if (line[i] < '0' || line[i] > '9')
			return (0);
		while (line[i] >= '0' && line[i] <= '9')
		{
			value = value * 10 + (line[i] - '0');
			count++;
			i++;
		}
		if (count == 0 || value > 255)
			return (0);
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (component < 2  && line[i++] != ',')
			return (0);
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		component++;
	}
	if (line[i] != '\0' && line[i] != '\n')
		return (0);
	return (1);
}

// Helper function to reallocate array
char **realloc_map(char **map, int old_size, int new_size)
{
	char **new_map;
	int i;

	new_map = malloc(sizeof(char *) * (new_size + 1));
	if (!new_map)
		return NULL;
	
	i = 0;
	while (i < old_size && map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	free(map);
	return new_map;
}
// int check_dup()
// {
    
// }

char *remove_backslash_n(char *line)
{
    int i;
    char *new_line;

    if (!line)
        return (NULL);

    i = 0;
    while (line[i] && line[i] != '\n')
        i++;

    new_line = malloc(i + 1);
    if (!new_line)
        return (NULL);

    int j = 0;
    while (j < i)
    {
        new_line[j] = line[j];
        j++;
    }
    new_line[j] = '\0';
    return (new_line);
}


char	**check_textures(char *map)
{
	int		fd;
	char	*line;
	int		tex_total = 0;
	int		dup[6] = {0};
	char	**map_extract = NULL;
	int		capacity = 10;
	int		count = 0;
	int		i;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (printf("have problem in fd of map check\n"), NULL);
	
	while ((line = get_next_line(fd)))
	{
        int j = 0;
        while (line[j] == 32 || (line[j] >= 9 && line[j] <= 13))
			j++;
		if (!line[j] || line[j] == '\n')
		{
			free(line);
			continue;
		}
		
		if (line[j] == '1')
		{
			map_extract = malloc(sizeof(char *) * (capacity + 1));
			if (!map_extract)
			{
				free(line);
				close(fd);
				return NULL;
			}
			map_extract[count++] = remove_backslash_n(line);
			while ((line = get_next_line(fd)))
			{
				if (count >= capacity)
				{
					capacity *= 2;
					map_extract = realloc_map(map_extract, count, capacity);
					if (!map_extract)
					{
						free(line);
						close(fd);
						return NULL;
					}
				}
				if (line[0] == '\n' || line[0] == '\0')
				{
						free(line);
						close(fd);
						return NULL;
				}
				
				map_extract[count++] = remove_backslash_n(line);
			}
			map_extract[count] = NULL;
			
			break;
		}
		
		if (line[j] == 'N' || line[j] == 'S' || line[j] == 'E' ||
			line[j] == 'W' || line[j] == 'F' || line[j] == 'C')
		{
			char *trimmed_line = line + j;
			
			if ((ft_strncmp(trimmed_line, "NO ", 3) == 0) && check_texture_filename(trimmed_line)) 
				{dup[0]++; tex_total++;}
			else if ((ft_strncmp(trimmed_line, "SO ", 3) == 0) && check_texture_filename(trimmed_line)) 
				{dup[1]++; tex_total++;}
			else if ((ft_strncmp(trimmed_line, "WE ", 3) == 0) && check_texture_filename(trimmed_line)) 
				{dup[2]++; tex_total++;}
			else if ((ft_strncmp(trimmed_line, "EA ", 3) == 0) && check_texture_filename(trimmed_line)) 
				{dup[3]++; tex_total++;}
			else if ((ft_strncmp(trimmed_line, "F ", 2) == 0) && check_rgb(trimmed_line)) 
				{dup[4]++; tex_total++;}
			else if ((ft_strncmp(trimmed_line, "C ", 2) == 0) && check_rgb(trimmed_line)) 
				{dup[5]++; tex_total++;}
			else 
			{ 
				free(line); 
				close(fd); 
				return NULL; 
			}
		}
		else if (line[j] != '\n')
		{
			free(line);
			close(fd);
			return NULL;
		}
		
		free(line);
	}
	close(fd);
	
	if (tex_total != 6)
		return NULL;
	i = 0;	
	while (i < 6)
	{
		if (dup[i] != 1)
			return NULL;
        i++;
	}
	
	return map_extract;
}

int check_neighbor(char **map, int i, int j)
{
    if (i < 0 || j < 0 || !map[i])         // outside map (above or left)
        return (1);
    if (j >= ft_strlen(map[i]))                // outside current line length
        return (1);
    if (map[i][j] == ' ')        // space means open void
        return (1);
    return (0);
}

int isvalidmap(char **map)
{
    int i = 0;
    int j = 0;
    while(map[i])
    {
        j = 0;
        while(map[i][j] == 32)
            j++;
        while(map[i][j])
        {
           if(map[i][j] == '0') 
           {
                if(check_neighbor(map, i - 1, j) || check_neighbor(map, i + 1, j) 
                    || check_neighbor(map, i, j - 1) || check_neighbor(map, i, j + 1))
                    return 1;
            }
            if(map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' 
                || map[i][j] == 'S') 
            {
                if(check_neighbor(map, i - 1, j) || check_neighbor(map, i + 1, j) 
                    || check_neighbor(map, i, j - 1) || check_neighbor(map, i, j + 1))
                    return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
} 
int checkmap(char **map)
{
    int k = 0;
    int i = 0;
    int j = 0;
    int player_counter = 0;
    printf("=== Collected Map ===\n");
	while (map[k])
		printf("%s\n" ,map[k++]);
	printf("=== End Map ===\n");
    printf("start checking");
    while(map[i])
    {
        j = 0;
        while(map[i][j] == 32)
            j++;
        while(map[i][j])
        {
            
            if(map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W'
                && map[i][j] != 'E' && map[i][j] != '0' && map[i][j] !='1' && map[i][j] != '\n')
                return 1;
            if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
                player_counter++;
            j++;
        }
        i++;
    }
    if(player_counter != 1)
        return 1;
    if(isvalidmap(map))
        return 1;
    return 0;
}
int check_validmap(char *mapfile_name)
{
    char **map = check_textures(mapfile_name);
    if(!map)
        return 1;
    if(checkmap(map))
        return 1;
    return 0;
}