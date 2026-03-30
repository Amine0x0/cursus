/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:30:00 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/17 20:07:52 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_tex_mapping(t_wall_draw *wall, t_ray *ray, t_texture *texture)
{
	double	step;
	int		window_height;
	int		line_height;

	window_height = wall->window_height;
	line_height = wall->line_height;
	wall->wall_x -= floor(wall->wall_x);
	wall->tex_x = (int)(wall->wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->dir_x < 0) || (ray->side == 1
			&& ray->dir_y > 0))
		wall->tex_x = texture->width - wall->tex_x - 1;
	step = STEP_FULL * texture->height / line_height;
	wall->tex_pos = (wall->draw_start - window_height / 2 + line_height / 2)
		* step;
}

static void	draw_column_pixel(t_game *game, t_texture *tex, t_wall_draw *wall)
{
	if (wall->y < wall->draw_start)
		draw_ceiling(game, wall->x, wall->y);
	else if (wall->y >= wall->draw_start && wall->y <= wall->draw_end)
	{
		draw_wall_pixel(game, tex, wall);
		wall->tex_pos += (STEP_FULL * tex->height / wall->line_height);
	}
	else
		draw_floor(game, wall->x, wall->y);
}

static void	calc_wall_x(t_game *game, t_ray *ray, t_wall_draw *wall)
{
	int	map_x;
	int	map_y;

	map_x = wall->map_x;
	map_y = wall->map_y;
	if (ray->side == 0)
		wall->wall_x = game->player.y + (map_x - game->player.x + (STEP_FULL
					- ray->step_x) / 2) / ray->dir_x * ray->dir_y;
	else
		wall->wall_x = game->player.x + (map_y - game->player.y + (STEP_FULL
					- ray->step_y) / 2) / ray->dir_y * ray->dir_x;
}

void	render_wall_column(t_game *game, t_texture *texture, t_wall_draw *wall,
		t_ray *ray)
{
	if (wall->line_height <= 0)
		return ;
	calc_wall_x(game, ray, wall);
	init_tex_mapping(wall, ray, texture);
	wall->y = 0;
	while (wall->y < game->window.height)
	{
		draw_column_pixel(game, texture, wall);
		wall->y++;
	}
}

void	render_column(t_game *game, t_ray *ray, t_wall_draw *wall)
{
	t_texture	*texture;

	if (ray->side == 0)
		wall->perp_dist = (wall->map_x - game->player.x + (STEP_FULL
					- ray->step_x) / 2) / ray->dir_x;
	else
		wall->perp_dist = (wall->map_y - game->player.y + (STEP_FULL
					- ray->step_y) / 2) / ray->dir_y;
	wall->line_height = (int)(game->window.height / wall->perp_dist);
	wall->draw_start = -wall->line_height / 2 + game->window.height / 2;
	if (wall->draw_start < 0)
		wall->draw_start = 0;
	wall->draw_end = wall->line_height / 2 + game->window.height / 2;
	if (wall->draw_end >= game->window.height)
		wall->draw_end = game->window.height - 1;
	texture = get_texture(game, ray);
	if (!texture || !texture->data)
		return ;
	wall->window_height = game->window.height;
	render_wall_column(game, texture, wall, ray);
}
