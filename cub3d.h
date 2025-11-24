/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:34:13 by ielouarr          #+#    #+#             */
/*   Updated: 2025/11/24 23:47:48 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
//get the next line part 

# ifndef BUFFER_SIZE
#define BUFFER_SIZE  2025
# endif


#define WIN_WIDTH  1280
#define WIN_HEIGHT 720


char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);


//cleaning 
typedef struct s_heap
{
	void			*address;
	struct s_heap	*next;
}	t_heap;

//structs

typedef struct s_color {
	int r;
	int g;
	int b;
} t_color;

typedef struct s_texture {
	char *no;
	char *so;
	char *we;
	char *ea;
} t_texture;

typedef struct s_map {
	char **grid;
	int width;
	int height;
} t_map;

typedef struct s_player {
	double x;
	double y;
	char dir;
	double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
} t_mlx;

typedef struct s_config {
	t_texture   textures;
	t_color     floor;
	t_color     ceiling;
	t_map       map;
    t_player    player;
	t_mlx       mlx;
	t_heap		*garbage; 
} t_config;

int ft_strnstr(char *haystack, char *needle, size_t len);
int ft_strncmp(const char *s1, const char *s2, size_t ncmp);
char	*get_next_line(int fd);
int check_validmap(char *mapfile_name, t_config *cfg);
int mapcollecting(t_config *config_list, char *map);
int	ft_strlen(char *senc);
char **get_rgb(char *rgbline, t_config *cfg);
char **realloc_map(char **map, int old_size, int new_size, t_config *cfg);
int	ft_atoi(const char *str);
char	*ft_itoa(int n, t_config *cfg);
char *remove_backslash_n(char *line, t_config *cfg);
void init_config(t_config *config);


//garbage_collector funcs
void	free_everything(t_heap *h, int exit);
void	*ft_malloc(size_t size, t_config *d);
t_heap	*g_c(int should_update,	t_heap *new_value);

#endif