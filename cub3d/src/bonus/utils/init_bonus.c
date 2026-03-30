/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:03:00 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/31 09:46:39 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	init_window_defaults(t_game *game)
{
	game->window.width = game->menu_width;
	game->window.height = game->menu_height;
	game->window.title = WINDOW_TITLE;
	game->running = true;
	game->in_menu = true;
	game->menu_fade_count = 0;
	game->game_fade_count = 0;
	ft_memset(&game->keys, 0, sizeof(t_keys));
}

bool	init_window(t_game *game)
{
	if (!game)
		return (false);
	log_event("Initializing window...", INFO);
	game->window.mlx = mlx_init();
	if (!game->window.mlx)
		return (log_event("mlx_init failed", ERROR), false);
	if (!init_menu_background(game))
	{
		log_event("Failed to load menu background, using defaults", ERROR);
		game->menu_width = 800;
		game->menu_height = 600;
	}
	else
		log_event("Menu background loaded successfully", SUCCESS);
	init_window_defaults(game);
	log_event("Window initialized successfully", SUCCESS);
	return (true);
}

bool	init_player(t_game *game)
{
	if (!game || !game->map.grid)
		return (false);
	log_event("Initializing player...", INFO);
	if (!search_player_position(game))
	{
		log_event("No player start found in map!", ERROR);
		return (false);
	}
	return (true);
}
