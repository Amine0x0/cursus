/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:57:52 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 16:57:54 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*main checks, and mlx initialization , a bit messy but it works*/
int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_putstr_fd("Error: MLX init failed\n", 2), 1);
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			WINDOW_TITLE);
	if (!data->win)
		return (free(data->mlx), ft_putstr_fd("Error: Window failed\n", 2), 1);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img)
	{
		mlx_destroy_window(data->mlx, data->win);
		free(data->mlx);
		return (ft_putstr_fd("Error: Image failed\n", 2), 1);
	}
	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	return (0);
}

int	init_all(t_data *data, t_grid *map, int argc, char **argv)
{
	if (argc != 2 || WINDOW_WIDTH > 1920 || WINDOW_HEIGHT > 1080)
		return (ft_putstr_fd("Usage: ./fdf <map.fdf>\n", 2), 1);
	if (check_map_file(argv[1]) == -1)
		return (ft_putstr_fd("map error <:3\n", 2), 1);
	if (init_mlx(data))
		return (1);
	init_data_values(data, map);
	return (0);
}

int	load_map(t_data *data, t_grid *map, char *filename)
{
	show_loading_screen(data);
	if (read_map(filename, map) == -1)
		return (ft_putstr_fd("Error: Map reading failed\n", 2), 1);
	data->map = map;
	data->min_z = map->grid[0][0].z;
	data->max_z = map->grid[0][0].z;
	find_min_max_z(data, map);
	data->finish_status = 1;
	return (0);
}

void	start_mlx_loop(t_data *data)
{
	draw_map(data);
	mlx_key_hook(data->win, handle_keypress, data);
	mlx_loop_hook(data->mlx, update_rotation, data);
	mlx_hook(data->win, 17, 0, handle_close, data);
	mlx_loop(data->mlx);
}
