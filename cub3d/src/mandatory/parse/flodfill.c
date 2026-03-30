/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flodfill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:12:18 by maboulah          #+#    #+#             */
/*   Updated: 2026/01/17 20:24:07 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	handle_neighbor(t_ff_context *ctx, int x, int y)
{
	if (is_open_cell(ctx, x, y))
		return (false);
	if (ctx->map[x][y] == '1' || ctx->map[x][y] == 'f')
		return (true);
	push_cell(ctx, x, y);
	return (true);
}

static bool	process_point(t_ff_context *ctx, t_point pt)
{
	if (!handle_neighbor(ctx, pt.x - 1, pt.y))
		return (false);
	if (!handle_neighbor(ctx, pt.x + 1, pt.y))
		return (false);
	if (!handle_neighbor(ctx, pt.x, pt.y - 1))
		return (false);
	if (!handle_neighbor(ctx, pt.x, pt.y + 1))
		return (false);
	return (true);
}

static bool	init_flood(t_ff_context *ctx, int x, int y)
{
	if (is_open_cell(ctx, x, y))
		return (false);
	if (ctx->map[x][y] == '1')
		return (true);
	push_cell(ctx, x, y);
	return (true);
}

bool	flood_fill(char **map, int x, int y, t_flood_fill_params p)
{
	t_ff_context	ctx;
	int				capacity;

	if (!map)
		return (false);
	capacity = p.width * p.height;
	ctx.map = map;
	ctx.stack = malloc(sizeof(t_point) * capacity);
	if (!ctx.stack)
		return (false);
	ctx.top = 0;
	ctx.params = p;
	if (!init_flood(&ctx, x, y))
		return (free(ctx.stack), false);
	while (ctx.top > 0)
	{
		if (!process_point(&ctx, ctx.stack[--ctx.top]))
			return (free(ctx.stack), false);
	}
	free(ctx.stack);
	return (true);
}
