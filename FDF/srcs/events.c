/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:22:24 by amabbadi          #+#    #+#             */
/*   Updated: 2025/03/27 16:22:25 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
/*anything event related , like the user clicking on smthing*/
int	handle_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	cleanup_and_exit(data);
	return (0);
}

void	zoom(t_data *data, int zoom_in)
{
	if (zoom_in)
		data->size += GRID_SIZE_INCREMENT;
	else if (data->size > MIN_GRID_SIZE)
		data->size -= GRID_SIZE_INCREMENT;
	else
		data->size = MIN_GRID_SIZE;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img_addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	draw_map(data);
}

void	translate_map(t_data *data, char direction)
{
	if (direction == 'w')
		data->translate_y -= TRANSLATE_INCREMENT;
	else if (direction == 's')
		data->translate_y += TRANSLATE_INCREMENT;
	else if (direction == 'a')
		data->translate_x -= TRANSLATE_INCREMENT;
	else if (direction == 'd')
		data->translate_x += TRANSLATE_INCREMENT;
	draw_map(data);
}

void	handle_movement_keys(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		translate_map(data, 'w');
	else if (keycode == KEY_S)
		translate_map(data, 's');
	else if (keycode == KEY_A)
		translate_map(data, 'a');
	else if (keycode == KEY_D)
		translate_map(data, 'd');
}

int	handle_keypress(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == KEY_O)
		zoom(data, 1);
	else if (keycode == KEY_I)
		zoom(data, 0);
	else if (keycode == KEY_ESC)
		cleanup_and_exit(data);
	else if (keycode == KEY_R)
		data->rotating = !data->rotating;
	else if (keycode == KEY_P)
		data->projection_mode = (data->projection_mode + 1) % 2;
	handle_rotation_keys(keycode, data);
	handle_movement_keys(keycode, data);
	draw_map(data);
	return (0);
}
