/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_helpers_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 03:44:10 by maboulah          #+#    #+#             */
/*   Updated: 2026/01/18 18:48:02 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	destroy_windows(t_game *game)
{
	if (!game->window.mlx)
		return ;
	if (game->window.win)
	{
		mlx_destroy_window(game->window.mlx, game->window.win);
		game->window.win = NULL;
	}
	if (game->menu_window)
	{
		mlx_destroy_window(game->window.mlx, game->menu_window);
		game->menu_window = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	if (game && game->window.mlx && game->window.win)
		mlx_mouse_show(game->window.mlx, game->window.win);
	destroy_textures(game);
	destroy_windows(game);
	if (game->map.grid)
		free_map_grid(game->map.grid);
	if (game->map.firstmap)
		free_map_grid(game->map.firstmap);
	free_map_info(&game->map.info);
	if (game->window.mlx)
	{
		mlx_destroy_display(game->window.mlx);
		free(game->window.mlx);
		game->window.mlx = NULL;
	}
}

void	free_map_grid(char **grid)
{
	int	i;

	i = 0;
	if (!grid)
		return ;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}
