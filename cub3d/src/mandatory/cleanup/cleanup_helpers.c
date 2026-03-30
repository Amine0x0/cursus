/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 03:31:34 by maboulah          #+#    #+#             */
/*   Updated: 2025/12/26 05:41:50 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_and_null(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_map_grid(char **grid)
{
	int	i;

	i = 0;
	if (!grid)
		return ;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	destroy_image_if_exists(void *mlx, void *img)
{
	if (img)
		mlx_destroy_image(mlx, img);
}
