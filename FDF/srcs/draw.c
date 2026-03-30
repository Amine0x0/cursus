/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:22:19 by amabbadi          #+#    #+#             */
/*   Updated: 2025/03/27 16:22:20 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
/*the main drawing logic , with its cleaning utils*/
void	free_transformed(t_coordinates **transformed, int height)
{
	int	y;

	if (!transformed)
		return ;
	y = 0;
	while (y < height)
	{
		free(transformed[y]);
		y++;
	}
	free(transformed);
}

void	set_line_params(int *p, t_coordinates s, t_coordinates e)
{
	p[0] = abs(e.x - s.x);
	p[1] = -abs(e.y - s.y);
	p[2] = 1;
	if (s.x >= e.x)
		p[2] = -1;
	p[3] = 1;
	if (s.y >= e.y)
		p[3] = -1;
	p[4] = p[0] + p[1];
}

void	draw_line(t_data *data, t_coordinates start, t_coordinates end)
{
	int	p[5];
	int	color;

	set_line_params(p, start, end);
	color = get_color(start, data->min_z, data->max_z);
	while (1)
	{
		put_pixel(data, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		update_position(p, &start);
	}
}

void	draw_map(t_data *data)
{
	t_projection	proj;
	t_coordinates	**transformed;

	init_projection_params(&proj, data);
	proj.offset_x = proj.center_x - (data->map->width \
		* data->size) / 2 + data->translate_x;
	proj.offset_y = proj.center_y - (data->map->height \
		* data->size) / 2 + data->translate_y;
	clear_image(data);
	mlx_clear_window(data->mlx, data->win);
	if (!allocate_transformed(&transformed, data))
		return ;
	init_transform(data, &proj, &transformed);
	draw_grid_lines(data, transformed);
	free_transformed(transformed, data->map->height);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	draw_controls(data);
}
