/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:59:12 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 16:59:13 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*utils for drawing purposes , like transforming the coordinates,
 updating the position of the pixel based on the window yadayada
 PS:
	p[0] = dx
	p[1] = -dy
	p[2] = step_x
	p[3] = step_y
	p[4] = error
*/
void	update_position(int *p, t_coordinates *pt)
{
	int	e2;

	e2 = 2 * p[4];
	if (e2 >= p[1])
	{
		p[4] += p[1];
		pt->x += p[2];
	}
	if (e2 <= p[0])
	{
		p[4] += p[0];
		pt->y += p[3];
	}
}

void	transform_coordinates(t_data *d, t_projection *p, t_coordinates *pt,
		int coords[2])
{
	pt->x = p->offset_x + coords[1] * d->size;
	pt->y = p->offset_y + coords[0] * d->size;
	pt->z = d->map->grid[coords[0]][coords[1]].z * HEIGHT_SCALE;
	pt->color = d->map->grid[coords[0]][coords[1]].color;
	if (d->projection_mode == ISOMETRIC_PROJECTION)
		apply_isometric(d, pt, p);
	else if (d->projection_mode == PARALLEL_PROJECTION)
		apply_parallel(&pt->x, &pt->y, pt->z, p);
}

void	draw_grid_lines(t_data *d, t_coordinates **t)
{
	int	y;
	int	x;

	y = -1;
	while (++y < d->map->height)
	{
		x = -1;
		while (++x < d->map->width)
		{
			if (x + 1 < d->map->width)
				draw_line(d, t[y][x], t[y][x + 1]);
			if (y + 1 < d->map->height)
				draw_line(d, t[y][x], t[y + 1][x]);
		}
	}
}

void	init_transform(t_data *d, t_projection *p, t_coordinates ***t)
{
	int	y;
	int	x;
	int	coords[2];

	y = -1;
	while (++y < d->map->height)
	{
		x = -1;
		while (++x < d->map->width)
		{
			coords[0] = y;
			coords[1] = x;
			transform_coordinates(d, p, &(*t)[y][x], coords);
		}
	}
}

/*more allocation utility ma3ndi fin ndirha*/
int	allocate_transformed(t_coordinates ***t, t_data *d)
{
	int	y;

	*t = malloc(sizeof(t_coordinates *) * d->map->height);
	if (!*t)
		return (0);
	y = -1;
	while (++y < d->map->height)
	{
		(*t)[y] = malloc(sizeof(t_coordinates) * d->map->width);
		if (!(*t)[y])
		{
			while (--y >= 0)
				free((*t)[y]);
			free(*t);
			return (0);
		}
	}
	return (1);
}
