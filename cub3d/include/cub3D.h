/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:00 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/18 17:53:34 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WINDOW_X 1280
# define WINDOW_Y 720
# define MOVE_SPEED 0.06
# define ROT_SPEED 0.05
# define WINDOW_TITLE "CUB3D"
# define CAMERA_OFFSET 2.0
# define PLAYER_OFFSET 0.5
# define DIR_PLANE_N 0.66
# define DIR_PLANE_W (-0.66)
# define STEP_FULL 1.0
# define MAX_RENDER_DIST 35
# define KEY_W 119
# define KEY_W_ALT 65362
# define KEY_S 115
# define KEY_S_ALT 65364
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# define SPRINT_MULTIPLIER 2.0

# include "../GNL/get_next_line.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_flood_fill_params
{
	int					height;
	int					width;
}						t_flood_fill_params;

typedef struct s_ff_context
{
	char				**map;
	t_point				*stack;
	int					top;
	t_flood_fill_params	params;
}						t_ff_context;

typedef struct s_map_info
{
	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;
	int					*floor_color;
	int					*ceiling_color;
}						t_map_info;

typedef enum e_log_type
{
	INFO,
	SUCCESS,
	ERROR
}						t_log_type;

typedef enum e_errors
{
	INIT,
	ARGS,
	MAP,
}						t_errors;

typedef struct s_texture
{
	void				*img;
	int					*data;
	int					width;
	int					height;
	int					bpp;
	int					line_length;
	int					endian;
}						t_texture;

typedef struct s_map
{
	char				**grid;
	char				**firstmap;
	int					width;
	int					height;
	t_map_info			info;
}						t_map;

typedef struct s_ray
{
	double				dir_x;
	double				dir_y;
	double				delta_x;
	double				delta_y;
	double				side_x;
	double				side_y;
	int					step_x;
	int					step_y;
	int					side;
	int					hit;
}						t_ray;

typedef struct s_wall_draw
{
	int					line_height;
	int					draw_start;
	int					draw_end;
	double				perp_dist;
	double				wall_x;
	int					tex_x;
	double				tex_pos;
	int					x;
	int					y;
	int					map_x;
	int					map_y;
	int					window_height;
}						t_wall_draw;

typedef struct s_player
{
	double				x;
	double				y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
}						t_player;

typedef struct s_window
{
	void				*mlx;
	void				*win;
	int					width;
	int					height;
	char				*title;
}						t_window;

typedef struct s_keys
{
	bool				w;
	bool				s;
	bool				a;
	bool				d;
	bool				left;
	bool				right;
}						t_keys;

typedef struct s_wall_textures
{
	t_texture			north;
	t_texture			south;
	t_texture			east;
	t_texture			west;
}						t_wall_textures;

typedef struct s_game
{
	t_window			window;
	t_map				map;
	t_player			player;
	t_wall_textures		wall_textures;
	t_keys				keys;
	t_texture			screen;
	bool				running;
}						t_game;

// parse
int						ft_count_it(char *s);
bool					handle_rgb_values(char **rgb, int **dst, char *found,
							int idx);
bool					handle_color(char **tokens, t_game *game, char *found);
bool					check_it(char *found);
char					*strim(char *s, int offset);
bool					ft_open(char *last);
int						is_line_valid(char **tokens);
void					handle_texture(char **tokens, t_game *game,
							char *found);
bool					flag(char *av);
char					*ft_strdup_new_line(const char *s);
bool					is_exist(char **text, t_game *game);
bool					check_text(t_game *game);
int						max_width(char **grid);
char					**pad_map(char **grid);
bool					ft_player(char **str);
char					**extract_map_lines(char **grid);
bool					extract_and_pad(t_game *game, char ***map_lines,
							char ***padded);
bool					find_start_position(char **padded, int rows, int *x,
							int *y);
bool					allocate_grid(char ***grid, char **padded, int rows);
bool					check_map1(t_game *game);
bool					flood_fill(char **map, int x, int y,
							t_flood_fill_params params);
bool					map_name(char *av);
void					setup_direction_south(t_game *game);
void					setup_direction_east(t_game *game);
void					setup_direction_west(t_game *game);
void					setup_direction_north(t_game *game);
void					free_str_array(char **arr);
size_t					ft_strlcpy(char *dst, const char *src, size_t dstsize);
void					calc_map_limits(char **grid, int *nums);
char					**copy_map_lines(char **grid, int *nums);

char					**ft_split(char const *s, char c);
int						ft_atoi(char *str);
void					err(t_errors type, char *reason);
bool					check_map(t_game *game, char *av);
bool					load_map(t_game *game, char *path);
bool					load_texture(void *mlx, t_texture *tex, char *path);
bool					load_wall_textures(t_game *game);
int						get_tex_pixel(t_texture *tex, int x, int y);
bool					init_screen(t_game *game);
void					draw_walls(t_game *game);
void					render_column(t_game *game, t_ray *ray,
							t_wall_draw *wall);
t_texture				*get_texture(t_game *game, t_ray *ray);
void					render_wall_column(t_game *game, t_texture *texture,
							t_wall_draw *wall, t_ray *ray);
void					draw_ceiling(t_game *game, int x, int y);
void					draw_floor(t_game *game, int x, int y);
void					draw_void_column(t_game *game, int x);
void					calc_perp_dist(t_ray *ray, t_wall_draw *wall,
							t_game *game);
bool					check_bounds(t_wall_draw *wall, t_game *game);
void					draw_wall_pixel(t_game *game, t_texture *texture,
							t_wall_draw *wall);
int						render(void *param);
void					move_player(t_game *game);
int						key_release(int keycode, t_game *game);
int						key_press(int keycode, t_game *game);
void					rotate_camera(t_game *game, double rotation_angle);
void					print_art(const char *path);
void					log_event(const char *msg, t_log_type type);
int						close_handler(void *param);
void					cleanup_game(t_game *game);
void					exit_game(t_game *game, int code);
void					free_map_info(t_map_info *info);
void					free_map_grid(char **grid);
bool					search_player_position(t_game *game);
bool					init_window(t_game *game);
bool					init_player(t_game *game);
int						ft_strcmp(const char *s1, const char *s2);
void					*ft_memset(void *b, int c, size_t len);
bool					is_open_cell(t_ff_context *ctx, int x, int y);
void					push_cell(t_ff_context *ctx, int x, int y);
#endif
