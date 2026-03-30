/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 03:31:34 by maboulah          #+#    #+#             */
/*   Updated: 2026/01/13 01:49:50 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	can_move_to(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_y < 0 || map_y >= game->map.height || !game->map.grid[map_y])
		return (false);
	if (map_x < 0 || map_x >= (int)ft_strlen(game->map.grid[map_y]))
		return (false);
	return (game->map.grid[map_y][map_x] == '0');
}

void	try_move(t_game *game, double new_x, double new_y)
{
	if (can_move_to(game, new_x, game->player.y))
		game->player.x = new_x;
	if (can_move_to(game, game->player.x, new_y))
		game->player.y = new_y;
}

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
}
