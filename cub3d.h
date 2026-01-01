/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-hai <moel-hai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:34:13 by ielouarr          #+#    #+#             */
/*   Updated: 2026/01/01 11:47:49 by moel-hai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <math.h>
//get the next line part 

# ifndef BUFFER_SIZE
#define BUFFER_SIZE  2025
# endif


#define WIN_WIDTH  1280
#define WIN_HEIGHT 720
#define PLAYER_SPEED 4
#define ROTATION_SPEED 0.05
#define FOV	0.66
#define ESC_KEY 53
#define W_KEY   13
#define A_KEY   0
#define S_KEY   1
#define D_KEY   2
#define LEFT_ARROW 123
#define RIGHT_ARROW 124
#define CLOSE_BUTTON 17



//cleaning 
typedef struct s_heap
{
	void			*address;
	struct s_heap	*next;
}	t_heap;

//structs

typedef struct s_keys
{
	int	a;
	int	d;
	int	w;
	int	s;
	int	right;
	int	left;
}	t_keys;

typedef struct s_color {
	int r;
	int g;
	int b;
} t_color;

typedef struct s_texture_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_texture_img;

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

typedef struct s_ray {
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
}	t_ray;

typedef struct s_config {
	t_texture   textures;      // paths to textures
	t_texture_img	tex_no;    // north texture image
	t_texture_img	tex_so;    // south texture image
	t_texture_img	tex_we;    // west texture image
	t_texture_img	tex_ea;    // east texture image
	t_color     floor;
	t_color     ceiling;
	t_map       map;
	t_player    player;
	t_mlx       mlx;
	t_keys		key;
	t_heap		*garbage; 
} t_config;


//parsing funcs

char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		ft_strnstr(char *haystack, char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t ncmp);
char	*get_next_line(int fd);
int		check_validmap(char *mapfile_name, t_config *cfg);
int		mapcollecting(t_config *config_list, char *map);
int		ft_strlen(char *senc);
char	**get_rgb(char *rgbline, t_config *cfg);
char	**realloc_map(char **map, int old_size, int new_size, t_config *cfg);
int		ft_atoi(const char *str);
char	*ft_itoa(int n, t_config *cfg);
char	*remove_backslash_n(char *line, t_config *cfg);
void	init_config(t_config *config);

// textures funcs 

int		load_texture(char *path, t_texture_img *tex, void *mlx);
int		load_all_textures(t_config *cfg);
int		get_texture_pixel(t_texture_img *tex, int x, int y);
void	destroy_texture(t_texture_img *tex, void *mlx);
void	destroy_all_textures(t_config *cfg);
void	destroy_mlx(t_config *cfg);
void	draw_textured_wall(t_config *cfg, t_ray *ray, int x);
t_texture_img	*select_texture(t_config *cfg, t_ray *ray);
double	calculate_wall_x(t_config *cfg, t_ray *ray);

//ray_casting funcs

int		run_game(t_config *configs);
void	init_player_vectors(t_config *cfg);
int		init_mlx(t_config *cfg);
void	init_ray_data(t_config *cfg, t_ray *ray, int x);
void	init_step_sidedist(t_config *cfg, t_ray *ray);
int		render_frame(t_config *cfg);
int		keys_update(t_config *cfg);
int		handle_key_press(int keycode, t_config *cfg);
int		handle_key_release(int keycode, t_config *cfg);
int		handle_close(t_config *cfg);
void    move_player(t_config *cfg, double dir_x, double dir_y);
void    rotate_player(t_config *cfg, double rot_speed);
void	put_pixel_to_img(t_mlx *mlx, int x, int y, int color);

//garbage_collector funcs

void	free_everything(t_heap *h, int exit);
void	*ft_malloc(size_t size, t_config *d);
t_heap	*g_c(int should_update,	t_heap *new_value);

#endif