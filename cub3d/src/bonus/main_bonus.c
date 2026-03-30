/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 03:50:23 by maboulah          #+#    #+#             */
/*   Updated: 2025/12/31 09:46:39 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	core_load(t_game *game, char **argv)
{
	if (!core_load_helper(argv, game))
		return (false);
	if (!open_menu_window(game))
		return (false);
	if (!setup_core_resources(game))
		return (false);
	log_event("Core load completed successfully", SUCCESS);
	return (true);
}

void	hooks(t_game *game)
{
	if (!game || !game->window.mlx || !game->menu_window)
		return ;
	log_event("Setting up hooks...", INFO);
	mlx_hook(game->menu_window, 2, (1L << 0), menu_key_handler, game);
	mlx_hook(game->menu_window, 17, 0, menu_close_handler, game);
	mlx_loop_hook(game->window.mlx, menu_loop, game);
	log_event("Entering main loop with menu", INFO);
	mlx_loop(game->window.mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		log_event("Usage: ./cub3D_bonus [map_path]", ERROR);
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
