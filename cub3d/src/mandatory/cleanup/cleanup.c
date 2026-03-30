/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 03:31:34 by maboulah          #+#    #+#             */
/*   Updated: 2026/01/18 18:47:57 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_and_null(void **ptr);
void	free_map_grid(char **grid);
void	destroy_image_if_exists(void *mlx, void *img);

void	free_map_info(t_map_info *info)
{
	free_and_null((void **)&info->no_texture);
	free_and_null((void **)&info->so_texture);
	free_and_null((void **)&info->ea_texture);
	free_and_null((void **)&info->we_texture);
	free_and_null((void **)&info->floor_color);
	free_and_null((void **)&info->ceiling_color);
}

void	destroy_textures(t_game *game)
{
	if (!game->window.mlx)
		return ;
	destroy_image_if_exists(game->window.mlx, game->wall_textures.north.img);
	destroy_image_if_exists(game->window.mlx, game->wall_textures.south.img);
	destroy_image_if_exists(game->window.mlx, game->wall_textures.east.img);
	destroy_image_if_exists(game->window.mlx, game->wall_textures.west.img);
	destroy_image_if_exists(game->window.mlx, game->screen.img);
}

void	destroy_windows(t_game *game)
{
	if (!game->window.mlx)
		return ;
	if (game->window.win)
	{
		mlx_destroy_window(game->window.mlx, game->window.win);
		game->window.win = NULL;
	}
}

void	cleanup_game(t_game *game)
{
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

void	exit_game(t_game *game, int code)
{
	cleanup_game(game);
	exit(code);
}
