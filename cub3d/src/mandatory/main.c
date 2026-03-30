/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:55:28 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/18 18:47:57 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	core_load_helper2(t_game *game)
{
	if (!load_wall_textures(game))
		return (log_event("Failed to load wall textures", ERROR),
			printf("Error\n"), false);
	if (!init_player(game))
		return (log_event("Failed to initialize player", ERROR),
			printf("Error\n"), false);
	if (!init_screen(game))
		return (log_event("Failed to initialize screen", ERROR),
			printf("Error\n"), false);
	return (true);
}

bool	core_load_helper(char **argv, t_game *game)
{
	if (!game || !argv || !argv[1])
		return (false);
	if (!load_map(game, argv[1]))
		return (log_event("Loading map failed", ERROR), printf("Error\n"),
			false);
	if (!check_map(game, argv[1]))
		return (log_event("Map check failed", ERROR), printf("Error\n"), false);
	if (!init_window(game))
		return (log_event("Error initializing window", ERROR),
			printf("Error\n"), false);
	return (true);
}

bool	core_load(t_game *game, char **argv)
{
	int	screen_w;
	int	screen_h;
	int	pos_x;
	int	pos_y;

	if (!core_load_helper(argv, game))
		return (false);
	mlx_get_screen_size(game->window.mlx, &screen_w, &screen_h);
	pos_x = (screen_w - game->window.width) / 2;
	pos_y = (screen_h - game->window.height) / 2;
	game->window.win = mlx_new_window(game->window.mlx, game->window.width,
			game->window.height, game->window.title);
	if (!game->window.win)
		return (log_event("Error opening game window", ERROR),
			printf("Error\n"), false);
	mlx_mouse_move(game->window.mlx, game->window.win, pos_x, pos_y);
	if (!core_load_helper2(game))
		return (false);
	return (true);
}

void	hooks(t_game *game)
{
	if (!game || !game->window.mlx || !game->window.win)
		return ;
	log_event("Setting up hooks...", INFO);
	mlx_hook(game->window.win, 2, (1L << 0), key_press, game);
	mlx_hook(game->window.win, 3, (1L << 1), key_release, game);
	mlx_hook(game->window.win, 17, 0, close_handler, game);
	mlx_loop_hook(game->window.mlx, render, game);
	log_event("Entering main game loop", INFO);
	mlx_loop(game->window.mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		log_event("Usage: ./cub3D [map_path]", ERROR);
		printf("Error\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	print_art("art/art.art");
	log_event("Cub3D is now starting...", INFO);
	if (!core_load(&game, argv))
	{
		cleanup_game(&game);
		return (1);
	}
	hooks(&game);
	return (0);
}
