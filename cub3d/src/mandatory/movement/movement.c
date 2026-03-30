/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:55:31 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/13 01:50:22 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	can_move_to(t_game *game, double new_x, double new_y);
void	try_move(t_game *game, double new_x, double new_y);
void	handle_key_mapping(int keycode, t_keys *keys, bool state);

int	key_press(int keycode, t_game *game)
{
	if (!game)
		return (0);
	handle_key_mapping(keycode, &game->keys, true);
	if (keycode == KEY_ESC)
		exit_game(game, 0);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (!game)
		return (0);
	handle_key_mapping(keycode, &game->keys, false);
	return (0);
}

void	move_player(t_game *game)
{
	double	speed;

	if (!game || !game->map.grid)
		return ;
	speed = MOVE_SPEED;
	if (game->keys.w)
		try_move(game, game->player.x + game->player.dir_x * speed,
			game->player.y + game->player.dir_y * speed);
	if (game->keys.s)
		try_move(game, game->player.x - game->player.dir_x * speed,
			game->player.y - game->player.dir_y * speed);
	if (game->keys.a)
		try_move(game, game->player.x - game->player.plane_x * speed,
			game->player.y - game->player.plane_y * speed);
	if (game->keys.d)
		try_move(game, game->player.x + game->player.plane_x * speed,
			game->player.y + game->player.plane_y * speed);
	if (game->keys.left)
		rotate_camera(game, -ROT_SPEED);
	if (game->keys.right)
		rotate_camera(game, ROT_SPEED);
}

void	rotate_camera(t_game *game, double rotation_angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_r;
	double	sin_r;

	if (!game)
		return ;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	cos_r = cos(rotation_angle);
	sin_r = sin(rotation_angle);
	game->player.dir_x = game->player.dir_x * cos_r - game->player.dir_y
		* sin_r;
	game->player.dir_y = old_dir_x * sin_r + game->player.dir_y * cos_r;
	game->player.plane_x = game->player.plane_x * cos_r - game->player.plane_y
		* sin_r;
	game->player.plane_y = old_plane_x * sin_r + game->player.plane_y * cos_r;
}
