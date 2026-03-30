/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:03:00 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/31 09:46:38 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	init_window(t_game *game)
{
	if (!game)
		return (false);
	log_event("Initializing window...", INFO);
	game->window.mlx = mlx_init();
	if (!game->window.mlx)
	{
		log_event("mlx_init failed", ERROR);
		return (false);
	}
	game->window.width = WINDOW_X;
	game->window.height = WINDOW_Y;
	game->window.title = WINDOW_TITLE;
	game->running = true;
	ft_memset(&game->keys, 0, sizeof(t_keys));
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
