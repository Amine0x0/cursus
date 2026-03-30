/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:22:12 by amabbadi          #+#    #+#             */
/*   Updated: 2025/03/27 16:22:13 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*pretty much contains all the function needed to allocate the grid and load 
the tokens from the map with some exit funcs and cleanup tools*/

void	cleanup_grid_rows(t_coordinates **grid, int i)
{
	while (i-- > 0)
		free(grid[i]);
	free(grid);
}

t_coordinates	**allocate_grid(int width, int height)
{
	t_coordinates	**grid;
	int				i;

	grid = malloc(sizeof(t_coordinates *) * height);
	if (!grid)
		return (NULL);
	i = 0;
	while (i < height)
	{
		grid[i] = malloc(sizeof(t_coordinates) * width);
		if (!grid[i])
		{
			cleanup_grid_rows(grid, i);
			return (NULL);
		}
		i++;
	}
	return (grid);
}

void	free_grid(t_coordinates **grid, int height)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	cleanup_mlx(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	cleanup_and_exit(t_data *data)
{
	if (data->map && data->map->grid)
		free_grid(data->map->grid, data->map->height);
	cleanup_mlx(data);
	exit(0);
}
