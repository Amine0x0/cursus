/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:24:43 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/17 20:24:44 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_open_cell(t_ff_context *ctx, int x, int y)
{
	if (x < 0 || x >= ctx->params.height || y < 0 || y >= ctx->params.width)
		return (true);
	if (ctx->map[x][y] == 'x' || ctx->map[x][y] == '\0')
		return (true);
	return (false);
}

void	push_cell(t_ff_context *ctx, int x, int y)
{
	ctx->map[x][y] = 'f';
	ctx->stack[ctx->top++] = (t_point){x, y};
}
