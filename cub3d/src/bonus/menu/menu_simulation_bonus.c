/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_simulation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:16 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/29 19:37:53 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

#define MENU_ROT_SPEED 0.002
#define FADE_DURATION 120

static int	calc_faded_color(int color, float fade_factor)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (int)(r * fade_factor);
	g = (int)(g * fade_factor);
	b = (int)(b * fade_factor);
	return ((r << 16) | (g << 8) | b);
}

static void	apply_fade_effect(t_game *game, int frame_count)
{
	float	fade_factor;
	int		total_pixels;
	int		i;

	if (!game || !game->screen.data)
		return ;
	if (frame_count >= FADE_DURATION)
		return ;
	fade_factor = (float)frame_count / FADE_DURATION;
	total_pixels = game->window.width * game->window.height;
	i = 0;
	while (i < total_pixels)
	{
		game->screen.data[i] = calc_faded_color(game->screen.data[i],
				fade_factor);
		i++;
	}
}

void	apply_game_fade(t_game *game)
{
	if (game->in_menu)
	{
		game->game_fade_count = 0;
		return ;
	}
	apply_fade_effect(game, game->game_fade_count);
	if (game->game_fade_count < FADE_DURATION)
		game->game_fade_count++;
}

static void	rotate_player_view(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	old_dir_x = game->player.dir_x;
	rot_speed = -MENU_ROT_SPEED;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y
		* cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y
		* cos(rot_speed);
}

void	simulate_menu_background(t_game *game)
{
	if (!game)
		return ;
	if (!game->in_menu)
	{
		game->menu_fade_count = 0;
		return ;
	}
	rotate_player_view(game);
	draw_walls(game);
	apply_fade_effect(game, game->menu_fade_count);
	if (game->menu_fade_count < FADE_DURATION)
		game->menu_fade_count++;
}
