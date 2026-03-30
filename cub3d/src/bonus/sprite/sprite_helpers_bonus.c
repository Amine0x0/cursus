/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_helpers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:21 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/29 19:37:53 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	set_bob_params(t_game *game, t_bob *bob)
{
	if (game->keys.shift)
		bob->speed_mult = 0.20;
	else
		bob->speed_mult = 0.1;
	if (game->keys.shift)
		bob->horiz_amp = 75.0;
	else
		bob->horiz_amp = 10.0;
	if (game->keys.shift)
		bob->vert_amp = 50.0;
	else
		bob->vert_amp = 8.0;
}

static void	apply_bobbing(t_game *game, t_bob *bob)
{
	game->hands.bob_timer += bob->speed_mult;
	bob->x = (int)(sin(game->hands.bob_timer) * bob->horiz_amp);
	bob->y = (int)(fabs(sin(game->hands.bob_timer * 2)) * bob->vert_amp);
	game->hands.screen_x = game->hands.base_x + bob->x;
	game->hands.screen_y = game->hands.base_y + bob->y;
}

static void	reset_bobbing(t_game *game)
{
	int	x;
	int	y;

	x = game->hands.base_x - game->hands.screen_x;
	y = game->hands.base_y - game->hands.screen_y;
	game->hands.screen_x += x / 5;
	game->hands.screen_y += y / 5;
	game->hands.bob_timer = 0.0;
}

void	update_hand_bobbing(t_game *game)
{
	t_bob	bob;

	if (!game || !game->hands.loaded)
		return ;
	if (game->keys.w || game->keys.s || game->keys.a || game->keys.d)
	{
		set_bob_params(game, &bob);
		apply_bobbing(game, &bob);
	}
	else
		reset_bobbing(game);
}

void	render_hand_sprite(t_game *game)
{
	if (game->hands.loaded)
	{
		update_hand_bobbing(game);
		draw_sprite(game, &game->hands);
	}
}
