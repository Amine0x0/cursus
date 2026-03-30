/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:45:01 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/06 23:45:29 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*includes*/
# include "GNL/get_next_line.h"
# include "libft/libft.h"
# include "/home/amabbadi/.local/lib/mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*Window based settings*/
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define WINDOW_TITLE "My fdf lul"

/*Grid settings*/
# define INITIAL_GRID_SIZE 2
# define MIN_GRID_SIZE 2
# define GRID_SIZE_INCREMENT 2
# define TRANSLATE_INCREMENT 5

/*rotation constants*/
# define ANGLE_SPEED 0.2
# define INITIAL_ANGLE_X 0
# define INITIAL_ANGLE_Y 0

/*height vars*/
# define HEIGHT_SCALE 2
# define COLOR_DENSITY 1

/*projection mode*/
# define ISOMETRIC_PROJECTION 0
# define PARALLEL_PROJECTION 1

/*consts*/
# define M_PI 3.14159265358979323846
# define BASE_16_CHARSET "0123456789ABCDEF"
# define BASE_16 16

/*colors*/
# define DEFAULT_COLOR 0xFFFFFF
# define TARGET_COLOR 0x00FF00

/*keys*/
# define KEY_ESC 65307
# define KEY_O 111
# define KEY_I 105
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_R 114
# define KEY_P 112
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

/*general structs*/
typedef struct s_dline
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
	int				color;
}					t_dline;

typedef struct s_coordinates
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_coordinates;

typedef struct s_control
{
	int				*y_offset;
	int				left_margin;
}					t_control;

typedef struct s_grid
{
	t_coordinates	**grid;
	int				width;
	int				height;
}					t_grid;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_grid			*map;
	int				size;
	int				min_z;
	int				max_z;
	int				projection_mode;
	double			angle_x;
	double			angle_y;
	int				rotating;
	int				translate_x;
	int				translate_y;
	int				finish_status;
}					t_data;

typedef struct s_projection
{
	int				center_x;
	int				center_y;
	double			angle_x;
	double			angle_y;
	double			max_dimension;
	double			iso_scale;
	double			height_scale;
	double			rotated_x;
	double			rotated_y;
	double			rotated_z;
	double			nx;
	double			ny;
	double			px;
	double			py;
	int				offset_x;
	int				offset_y;
}					t_projection;

/*function prototypes*/
void				cleanup_grid_rows(t_coordinates **grid, int i);
t_coordinates		**allocate_grid(int width, int height);
void				free_grid(t_coordinates **grid, int height);
void				cleanup_mlx(t_data *data);
void				cleanup_and_exit(t_data *data);
int					calculate_component(int default_c, int target_c, float t);
int					calculate_color(t_coordinates point, int range, int min_z);
int					get_color(t_coordinates point, int min_z, int max_z);
void				update_position(int *p, t_coordinates *pt);
void				transform_coordinates(t_data *d, t_projection *p,
						t_coordinates *pt, int coords[2]);
void				draw_grid_lines(t_data *d, t_coordinates **t);
void				init_transform(t_data *d, t_projection *p,
						t_coordinates ***t);
int					allocate_transformed(t_coordinates ***t, t_data *d);
void				free_transformed(t_coordinates **transformed, int height);
void				set_line_params(int *p, t_coordinates s, t_coordinates e);
void				draw_line(t_data *data, t_coordinates start,
						t_coordinates end);
void				draw_map(t_data *data);
int					handle_close(void *param);
void				zoom(t_data *data, int zoom_in);
void				translate_map(t_data *data, char direction);
void				handle_movement_keys(int keycode, t_data *data);
int					handle_keypress(int keycode, void *param);
int					is_valid_input(char *line);
int					check_map_file(char *file);
int					check_ext(char *file);
int					init_mlx(t_data *data);
int					init_all(t_data *data, t_grid *map, int argc, char **argv);
int					load_map(t_data *data, t_grid *map, char *filename);
void				start_mlx_loop(t_data *data);
void				init_data_values(t_data *data, t_grid *map);
char				*get_projection_name(t_data *data);
void				show_loading_screen(t_data *data);
void				clear_image(t_data *data);
int					read_file_lines(const char *filename, int *max_cols,
						int *rows);
int					determine_dimensions_and_allocate(const char *filename,
						t_grid *map, int *max_cols, int *rows);
int					read_and_process_rows(const char *filename, t_grid *map);
int					populate_grid(const char *filename, t_grid *map);
int					read_map(const char *filename, t_grid *map);
int					ft_isspace(int c);
int					get_base_index(char c, char *base, int base_len);
int					ft_atoi_base(const char *str, int str_base);
void				find_min_max_z(t_data *data, t_grid *map);
int					process_token(char *token, t_coordinates *point);
int					process_line(char *line, int *current_cols);
int					process_row(t_grid *map, char **tokens, int row);
void				init_projection_params(t_projection *params, t_data *data);
void				apply_parallel(int *x, int *y, int z, t_projection *p);
void				apply_isometric(t_data *d, t_coordinates *pt,
						t_projection *p);
void				handle_rotation_keys(int keycode, t_data *data);
void				put_pixel(t_data *data, int x, int y, int color);

void				draw_controls(t_data *data);
int					update_rotation(void *param);

#endif
