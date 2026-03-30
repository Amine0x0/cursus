/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:12 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/17 20:24:07 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	init_ray_step(t_ray *ray, t_game *game)
{
	if (ray->dir_x < 0)
		ray->side_x = (game->player.x - (int)game->player.x) * ray->delta_x;
	else
		ray->side_x = ((int)game->player.x + STEP_FULL - game->player.x)
			* ray->delta_x;
	if (ray->dir_y < 0)
		ray->side_y = (game->player.y - (int)game->player.y) * ray->delta_y;
	else
		ray->side_y = ((int)game->player.y + STEP_FULL - game->player.y)
			* ray->delta_y;
	ray->hit = 0;
	ray->side = 0;
}

void	init_ray(t_ray *ray, t_game *game, double camera_x)
{
	ray->dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->delta_x = fabs(STEP_FULL / ray->dir_x);
	ray->delta_y = fabs(STEP_FULL / ray->dir_y);
	if (ray->dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
	init_ray_step(ray, game);
}

int	cast_ray(t_ray *ray, t_game *game, t_wall_draw *wall)
{
	wall->map_x = (int)game->player.x;
	wall->map_y = (int)game->player.y;
	while (1)
	{
		ray_step(ray, wall);
		calc_perp_dist(ray, wall, game);
		if (wall->perp_dist > MAX_RENDER_DIST)
			return (0);
		if (check_bounds(wall, game))
			return (0);
		if (game->map.grid[wall->map_y][wall->map_x] == '1'
			|| game->map.grid[wall->map_y][wall->map_x] == 'D')
			return (1);
	}
	return (0);
}

t_texture	*get_texture(t_game *game, t_ray *ray, t_wall_draw *wall)
{
	char	hit_cell;

	hit_cell = game->map.grid[wall->map_y][wall->map_x];
	if (hit_cell == 'D')
		return (&game->wall_textures.door);
	if (ray->side == 0 && ray->step_x > 0)
		return (&game->wall_textures.east);
	if (ray->side == 0 && ray->step_x < 0)
		return (&game->wall_textures.west);
	if (ray->side == 1 && ray->step_y > 0)
		return (&game->wall_textures.south);
	return (&game->wall_textures.north);
}
