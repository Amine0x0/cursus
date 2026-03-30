/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_helpers2_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:30:00 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/29 19:37:53 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	setup_direction_south(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->player.plane_x = DIR_PLANE_W;
	game->player.plane_y = 0;
}

void	setup_direction_east(t_game *game)
{
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = DIR_PLANE_N;
}

void	setup_direction_west(t_game *game)
{
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = DIR_PLANE_W;
}

void	setup_direction_north(t_game *game)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plane_x = DIR_PLANE_N;
	game->player.plane_y = 0;
}
