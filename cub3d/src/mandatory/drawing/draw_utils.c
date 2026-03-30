/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 18:30:00 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/17 20:03:13 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_ceiling(t_game *game, int x, int y)
{
	int	ceiling_col;
	int	*c;

	if (!game->map.info.ceiling_color)
		return ;
	c = game->map.info.ceiling_color;
	ceiling_col = ((c[0] & 0xFF) << 16) | ((c[1] & 0xFF) << 8) | (c[2] & 0xFF);
	game->screen.data[y * game->window.width + x] = ceiling_col;
}

void	draw_floor(t_game *game, int x, int y)
{
	int	floor_col;
	int	*f;

	if (!game->map.info.floor_color)
		return ;
	f = game->map.info.floor_color;
	floor_col = ((f[0] & 0xFF) << 16) | ((f[1] & 0xFF) << 8) | (f[2] & 0xFF);
	game->screen.data[y * game->window.width + x] = floor_col;
}

void	draw_wall_pixel(t_game *game, t_texture *texture, t_wall_draw *wall)
{
	int	tex_y;
	int	color;

	tex_y = (int)wall->tex_pos;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	color = get_tex_pixel(texture, wall->tex_x, tex_y);
	game->screen.data[wall->y * game->window.width + wall->x] = color;
}

t_texture	*get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0 && ray->step_x > 0)
		return (&game->wall_textures.east);
	if (ray->side == 0 && ray->step_x < 0)
		return (&game->wall_textures.west);
	if (ray->side == 1 && ray->step_y > 0)
		return (&game->wall_textures.south);
	return (&game->wall_textures.north);
}

int	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game || !game->window.mlx || !game->window.win || !game->screen.img)
		return (0);
	move_player(game);
	draw_walls(game);
	mlx_put_image_to_window(game->window.mlx, game->window.win,
		game->screen.img, 0, 0);
	return (0);
}
