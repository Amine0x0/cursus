/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:24 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/31 09:46:39 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	can_move_to(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_y < 0 || map_y >= game->map.height || !game->map.grid[map_y])
		return (false);
	if (map_x < 0 || map_x >= (int)ft_strlen(game->map.grid[map_y]))
		return (false);
	return (game->map.grid[map_y][map_x] == '0'
		|| game->map.grid[map_y][map_x] == 'O');
}

void	try_move(t_game *game, double new_x, double new_y)
{
	if (can_move_to(game, new_x, game->player.y))
		game->player.x = new_x;
	if (can_move_to(game, game->player.x, new_y))
		game->player.y = new_y;
}

static void	init_directions(int directions[4][2])
{
	directions[0][0] = 0;
	directions[0][1] = -1;
	directions[1][0] = 0;
	directions[1][1] = 1;
	directions[2][0] = -1;
	directions[2][1] = 0;
	directions[3][0] = 1;
	directions[3][1] = 0;
}

static void	toggle_door_cell(char *cell)
{
	if (*cell == 'D')
		*cell = 'O';
	else if (*cell == 'O')
		*cell = 'D';
}

void	check_door_at_offset(t_game *game, int px, int py, int offset)
{
	int	directions[4][2];
	int	dx;
	int	dy;
	int	tx;
	int	ty;

	init_directions(directions);
	dx = directions[offset][0];
	dy = directions[offset][1];
	tx = px + dx;
	ty = py + dy;
	if (ty < 0 || ty >= game->map.height || tx < 0 || !game->map.grid[ty]
		|| tx >= (int)ft_strlen(game->map.grid[ty]))
		return ;
	toggle_door_cell(&game->map.grid[ty][tx]);
}
