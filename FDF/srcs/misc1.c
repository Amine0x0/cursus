/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:22:51 by amabbadi          #+#    #+#             */
/*   Updated: 2025/03/27 16:22:52 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*random goofy funcs*/
int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	get_base_index(char c, char *base, int base_len)
{
	int	i;

	i = 0;
	while (i < base_len)
	{
		if (ft_toupper(c) == base[i])
			return (i);
		i++;
	}
	return (-1);
}

void	find_min_max_z(t_data *data, t_grid *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x].z < data->min_z)
				data->min_z = map->grid[y][x].z;
			if (map->grid[y][x].z > data->max_z)
				data->max_z = map->grid[y][x].z;
			x++;
		}
		y++;
	}
}

char	*get_projection_name(t_data *data)
{
	if (data->projection_mode == ISOMETRIC_PROJECTION)
		return ("Isometric");
	else
		return ("Parallel");
}
