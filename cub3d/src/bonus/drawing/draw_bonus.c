/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:12 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/17 20:16:19 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_ray(t_ray *ray, t_game *game, double camera_x);
int		cast_ray(t_ray *ray, t_game *game, t_wall_draw *wall);

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
	texture = get_texture(game, ray, wall);
	if (!texture || !texture->data)
		return ;
	wall->window_height = game->window.height;
	render_wall_column(game, texture, wall, ray);
}

int	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game || !game->window.mlx || !game->window.win || !game->screen.img)
		return (0);
	if (game->in_menu)
		return (0);
	move_player(game);
	handle_mouse_rotation(game);
	draw_walls(game);
	apply_game_fade(game);
	render_hand_sprite(game);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->screen.img, 0, 0);
	return (0);
}
