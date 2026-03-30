/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:53 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/26 04:54:54 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	close_handler(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game)
		return (0);
	log_event("Window closed", INFO);
	exit_game(game, 0);
	return (0);
}
