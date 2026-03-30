/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:25:03 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/17 20:25:04 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	calc_perp_dist(t_ray *ray, t_wall_draw *wall, t_game *game)
{
	if (ray->side == 0)
		wall->perp_dist = (wall->map_x - game->player.x + (STEP_FULL
					- ray->step_x) / 2) / ray->dir_x;
	else
		wall->perp_dist = (wall->map_y - game->player.y + (STEP_FULL
					- ray->step_y) / 2) / ray->dir_y;
}

bool	check_bounds(t_wall_draw *wall, t_game *game)
{
	if (wall->map_y < 0 || wall->map_y >= game->map.height
		|| !game->map.grid[wall->map_y] || wall->map_x < 0
		|| wall->map_x >= (int)ft_strlen(game->map.grid[wall->map_y]))
		return (true);
	return (false);
}

void	ray_step(t_ray *ray, t_wall_draw *wall)
{
	if (ray->side_x < ray->side_y)
	{
		ray->side_x += ray->delta_x;
		wall->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_y += ray->delta_y;
		wall->map_y += ray->step_y;
		ray->side = 1;
	}
}
