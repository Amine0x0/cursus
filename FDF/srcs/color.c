/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:58:49 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 16:58:49 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*anything color related hh (rwina hna)*/
int	calculate_component(int default_c, int target_c, float t)
{
	return ((int)(default_c + t * (target_c - default_c)));
}

int	calculate_color(t_coordinates point, int range, int min_z)
{
	float	t;
	int		r;
	int		g;
	int		b;

	t = pow(fmin(fmax((float)(point.z - min_z) / range, 0.0), 1.0),
			COLOR_DENSITY);
	r = calculate_component((DEFAULT_COLOR >> 16) & 0xFF,
			(TARGET_COLOR >> 16) & 0xFF, t);
	g = calculate_component((DEFAULT_COLOR >> 8) & 0xFF,
			(TARGET_COLOR >> 8) & 0xFF, t);
	b = calculate_component(DEFAULT_COLOR & 0xFF, TARGET_COLOR & 0xFF, t);
	return ((r << 16) | (g << 8) | b);
}

int	get_color(t_coordinates point, int min_z, int max_z)
{
	int	range;

	if (point.color != DEFAULT_COLOR)
		return (point.color);
	range = max_z - min_z;
	if (range == 0)
		return (DEFAULT_COLOR);
	return (calculate_color(point, range, min_z));
}
