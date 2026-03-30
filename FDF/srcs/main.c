/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:22:37 by amabbadi          #+#    #+#             */
/*   Updated: 2025/03/27 16:22:39 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*sets up the initial values I will work with in the rest of the program*/
void	init_data_values(t_data *data, t_grid *map)
{
	data->map = map;
	data->size = INITIAL_GRID_SIZE;
	data->projection_mode = ISOMETRIC_PROJECTION;
	data->angle_x = 0;
	data->angle_y = 0;
	data->rotating = 0;
	data->translate_x = 0;
	data->translate_y = 0;
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
	data->finish_status = 0;
}

/*the main loading screen , appears before the map is
fully drawn*/
void	show_loading_screen(t_data *data)
{
	int		center_x;
	int		center_y;
	char	*frames;

	center_x = WINDOW_WIDTH / 2 - 100;
	center_y = WINDOW_HEIGHT / 2;
	frames = "The map is Loading";
	mlx_clear_window(data->mlx, data->win);
	while (data->finish_status == 0)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_string_put(data->mlx, data->win, center_x, center_y, 0xFFFFFF,
			frames);
		mlx_do_sync(data->mlx);
		usleep(100000);
		data->finish_status = 1;
	}
}

/*clears the whole image by settings everything to 0*/
void	clear_image(t_data *data)
{
	ft_memset(data->img_addr, 0, WINDOW_WIDTH * WINDOW_HEIGHT
		* (data->bits_per_pixel / 8));
}

/*checks whether the coordinates of the point are within
 the window bounds , and updates its color*/
void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = data->img_addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/*where everything basically starts, the main function*/
int	main(int argc, char **argv)
{
	t_data	data;
	t_grid	map;

	if (init_all(&data, &map, argc, argv))
		return (1);
	if (load_map(&data, &map, argv[1]))
		return (cleanup_and_exit(&data), 1);
	start_mlx_loop(&data);
	cleanup_and_exit(&data);
	return (0);
}
