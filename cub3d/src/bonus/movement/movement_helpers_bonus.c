/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_helpers_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:24 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/29 19:17:07 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	handle_key_mapping(int keycode, t_keys *keys, bool state)
{
	if (keycode == KEY_W || keycode == KEY_W_ALT)
		keys->w = state;
	else if (keycode == KEY_S || keycode == KEY_S_ALT)
		keys->s = state;
	else if (keycode == KEY_A)
		keys->a = state;
	else if (keycode == KEY_D)
		keys->d = state;
	else if (keycode == KEY_LEFT)
		keys->left = state;
	else if (keycode == KEY_RIGHT)
		keys->right = state;
	else if (keycode == KEY_SHIFT_L || keycode == KEY_SHIFT_R)
		keys->shift = state;
}

void	handle_mouse_rotation(t_game *game)
{
	static t_mouse	mouse = {-1, -1, -1, false, 0.003};
	int				delta_x;

	if (!game || !game->window.mlx || !game->window.win)
		return ;
	if (!mlx_mouse_get_pos(game->window.mlx, game->window.win, &mouse.x,
			&mouse.y))
		return ;
	if (!mouse.initialized)
	{
		mouse.last_x = mouse.x;
		mouse.initialized = true;
		return ;
	}
	delta_x = mouse.x - mouse.last_x;
	if (delta_x != 0)
		rotate_camera(game, delta_x * mouse.sens);
	mouse.last_x = mouse.x;
	if (mouse.x < game->window.width / 4 || mouse.x > (3 * game->window.width)
		/ 4)
	{
		mouse.last_x = game->window.width / 2;
		mlx_mouse_move(game->window.mlx, game->window.win, mouse.last_x,
			mouse.y);
	}
}

int	mouse_motion_handler(int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	(void)game;
	return (0);
}
