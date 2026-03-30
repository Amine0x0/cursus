/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 05:43:15 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/17 20:16:19 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	init_screen(t_game *game)
{
	if (!game || !game->window.mlx)
		return (false);
	game->screen.img = mlx_new_image(game->window.mlx, game->window.width,
			game->window.height);
	if (!game->screen.img)
		return (false);
	game->screen.data = (int *)mlx_get_data_addr(game->screen.img,
			&game->screen.bpp, &game->screen.line_length, &game->screen.endian);
	if (!game->screen.data)
		return (false);
	return (true);
}

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

static void	init_ray(t_ray *ray, t_game *game, double camera_x)
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

static int	cast_ray(t_ray *ray, t_game *game, t_wall_draw *wall)
{
	wall->map_x = (int)game->player.x;
	wall->map_y = (int)game->player.y;
	while (1)
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
		calc_perp_dist(ray, wall, game);
		if (wall->perp_dist > MAX_RENDER_DIST)
			return (0);
		if (check_bounds(wall, game))
			return (0);
		if (game->map.grid[wall->map_y][wall->map_x] == '1')
			return (1);
	}
	return (0);
}

void	draw_walls(t_game *game)
{
	int			x;
	t_ray		ray;
	t_wall_draw	wall;

	if (!game || !game->screen.data || !game->map.grid
		|| !game->map.info.floor_color || !game->map.info.ceiling_color)
		return ;
	x = 0;
	while (x < game->window.width)
	{
		init_ray(&ray, game, CAMERA_OFFSET * x / (double)game->window.width
			- STEP_FULL);
		wall.x = x;
		if (cast_ray(&ray, game, &wall))
			render_column(game, &ray, &wall);
		else
			draw_void_column(game, x);
		x++;
	}
}
