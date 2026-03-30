/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_helpers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:21 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/29 19:17:07 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	init_keys_false(t_game *game)
{
	game->keys.w = false;
	game->keys.s = false;
	game->keys.a = false;
	game->keys.d = false;
	game->keys.left = false;
	game->keys.right = false;
	game->keys.shift = false;
}

void	setup_game_hooks(t_game *game)
{
	mlx_hook(game->window.win, 2, (1L << 0), key_press, game);
	mlx_hook(game->window.win, 3, (1L << 1), key_release, game);
	mlx_hook(game->window.win, 6, (1L << 6), mouse_motion_handler, game);
	mlx_hook(game->window.win, 17, 0, close_handler, game);
	mlx_loop_hook(game->window.mlx, render, game);
}

int	menu_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return (0);
	if (game->in_menu)
		draw_menu(game);
	return (0);
}

int	menu_close_handler(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return (0);
	log_event("Exiting from menu...", INFO);
	exit_game(game, 0);
	return (0);
}
