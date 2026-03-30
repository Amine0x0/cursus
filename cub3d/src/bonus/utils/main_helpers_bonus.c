/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:30:00 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/18 18:17:29 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	core_load_helper(char **argv, t_game *game)
{
	if (!game || !argv || !argv[1])
		return (false);
	log_event("Starting core load...", INFO);
	if (!load_map(game, argv[1]))
		return (log_event("Loading map failed", ERROR), false);
	log_event("Map loaded successfully", SUCCESS);
	if (!check_map(game, argv[1]))
		return (log_event("Map check failed", ERROR), false);
	log_event("Map check passed", SUCCESS);
	if (!init_window(game))
		return (log_event("Error initializing window", ERROR), false);
	return (true);
}

bool	open_menu_window(t_game *game)
{
	int	screen_w;
	int	screen_h;
	int	pos_x;
	int	pos_y;

	mlx_get_screen_size(game->window.mlx, &screen_w, &screen_h);
	pos_x = (screen_w - game->menu_width) / 2;
	pos_y = (screen_h - game->menu_height) / 2;
	game->menu_window = mlx_new_window(game->window.mlx, game->menu_width,
			game->menu_height, "CUB3D - Menu");
	if (!game->menu_window)
		return (log_event("Error opening menu window", ERROR), false);
	mlx_mouse_move(game->window.mlx, game->menu_window, pos_x, pos_y);
	log_event("Menu window opened successfully", SUCCESS);
	return (true);
}

bool	setup_core_resources(t_game *game)
{
	if (!load_wall_textures(game))
		return (log_event("Failed to load wall textures", ERROR), false);
	log_event("Wall textures loaded successfully", SUCCESS);
	if (!init_player(game))
		return (log_event("Failed to initialize player", ERROR), false);
	if (!init_screen(game))
		return (log_event("Failed to initialize screen", ERROR), false);
	log_event("Screen initialized successfully", SUCCESS);
	return (true);
}
