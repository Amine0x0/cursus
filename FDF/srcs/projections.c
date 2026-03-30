/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:22:57 by amabbadi          #+#    #+#             */
/*   Updated: 2025/03/27 16:22:57 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*the projections woohoo*/
void	init_projection_params(t_projection *params, t_data *data)
{
	params->center_x = WINDOW_WIDTH / 2;
	params->center_y = WINDOW_HEIGHT / 2;
	params->max_dimension = fmax(data->map->width, data->map->height)
		* data->size;
	params->iso_scale = cos(M_PI / 6);
	params->height_scale = HEIGHT_SCALE;
	params->angle_x = data->angle_x;
	params->angle_y = data->angle_y;
	params->rotated_x = 0;
	params->rotated_y = 0;
	params->rotated_z = 0;
	params->px = 0;
	params->py = 0;
	params->offset_x = 0;
	params->offset_y = 0;
}

void	apply_parallel(int *x, int *y, int z, t_projection *p)
{
	(void)z;
	p->px = *x - p->center_x;
	p->py = *y - p->center_y;
	p->nx = p->px + p->angle_x;
	p->ny = p->py + p->angle_y;
	*x = (int)round(p->nx + p->center_x);
	*y = (int)round(p->ny + p->center_y);
}

void	apply_isometric(t_data *d, t_coordinates *pt, t_projection *p)
{
	(void)d;
	p->px = pt->x - p->center_x;
	p->py = pt->y - p->center_y;
	p->rotated_y = p->py * cos(p->angle_x) - pt->z * sin(p->angle_x);
	p->rotated_z = p->py * sin(p->angle_x) + pt->z * cos(p->angle_x);
	p->rotated_x = p->px * cos(p->angle_y) + p->rotated_z * sin(p->angle_y);
	p->rotated_z = -p->px * sin(p->angle_y) + p->rotated_z * cos(p->angle_y);
	pt->x = (int)round((p->rotated_x - p->rotated_y) * p->iso_scale)
		+ p->center_x;
	pt->y = (int)round((p->rotated_x + p->rotated_y) * p->iso_scale / 2)
		- p->rotated_z * p->height_scale + p->center_y;
}
