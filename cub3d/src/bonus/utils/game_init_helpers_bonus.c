/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_helpers_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:30:00 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/29 19:37:53 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static bool	is_player_char(char c);
static void	set_player_direction(t_game *game, int x, int y, char dir);

static bool	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	search_player_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		if (game->map.grid[y])
		{
			x = 0;
			while (x < game->map.width)
			{
				if (is_player_char(game->map.grid[y][x]))
				{
					set_player_direction(game, x, y, game->map.grid[y][x]);
					log_event("Player position set", SUCCESS);
					return (true);
				}
				x++;
			}
		}
		y++;
	}
	return (false);
}

static void	setup_player_pos(t_game *game, int x, int y)
{
	game->player.x = x + PLAYER_OFFSET;
	game->player.y = y + PLAYER_OFFSET;
	game->map.grid[y][x] = '0';
}

static void	set_player_direction(t_game *game, int x, int y, char dir)
{
	setup_player_pos(game, x, y);
	if (dir == 'N')
		setup_direction_north(game);
	else if (dir == 'S')
		setup_direction_south(game);
	else if (dir == 'E')
		setup_direction_east(game);
	else
		setup_direction_west(game);
}
