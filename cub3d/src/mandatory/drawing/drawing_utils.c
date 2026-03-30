/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:24:47 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/17 20:24:51 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
