/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 03:48:37 by maboulah          #+#    #+#             */
/*   Updated: 2025/12/29 19:17:07 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	free_and_null(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_map_info(t_map_info *info)
{
	free_and_null((void **)&info->no_texture);
	free_and_null((void **)&info->so_texture);
	free_and_null((void **)&info->ea_texture);
	free_and_null((void **)&info->we_texture);
	free_and_null((void **)&info->floor_color);
	free_and_null((void **)&info->ceiling_color);
}

static void	destroy_image_if_exists(void *mlx, void *img)
{
	if (img)
		mlx_destroy_image(mlx, img);
}

void	destroy_textures(t_game *game)
{
	if (!game->window.mlx)
		return ;
	destroy_image_if_exists(game->window.mlx, game->wall_textures.north.img);
	destroy_image_if_exists(game->window.mlx, game->wall_textures.south.img);
	destroy_image_if_exists(game->window.mlx, game->wall_textures.east.img);
	destroy_image_if_exists(game->window.mlx, game->wall_textures.west.img);
	destroy_image_if_exists(game->window.mlx, game->wall_textures.door.img);
	destroy_image_if_exists(game->window.mlx, game->menu_bg.img);
	destroy_image_if_exists(game->window.mlx, game->screen.img);
	destroy_image_if_exists(game->window.mlx, game->hands.texture.img);
}

void	exit_game(t_game *game, int code)
{
	cleanup_game(game);
	exit(code);
}
