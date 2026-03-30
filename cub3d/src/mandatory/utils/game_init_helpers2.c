/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulah <maboulah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:40:54 by maboulah          #+#    #+#             */
/*   Updated: 2025/12/27 18:44:11 by maboulah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
