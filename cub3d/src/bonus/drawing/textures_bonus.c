/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:35 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/17 20:24:07 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	load_texture(void *mlx, t_texture *tex, char *path)
{
	if (!mlx || !tex || !path)
		return (false);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (false);
	tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length,
			&tex->endian);
	if (!tex->data)
		return (false);
	return (true);
}

bool	load_wall_textures(t_game *game)
{
	if (!game || !game->window.mlx || !game->map.info.no_texture
		|| !game->map.info.so_texture || !game->map.info.ea_texture
		|| !game->map.info.we_texture)
		return (false);
	if (!load_texture(game->window.mlx, &game->wall_textures.north,
			game->map.info.no_texture))
		return (false);
	if (!load_texture(game->window.mlx, &game->wall_textures.south,
			game->map.info.so_texture))
		return (false);
	if (!load_texture(game->window.mlx, &game->wall_textures.east,
			game->map.info.ea_texture))
		return (false);
	if (!load_texture(game->window.mlx, &game->wall_textures.west,
			game->map.info.we_texture))
		return (false);
	if (!load_texture(game->window.mlx, &game->wall_textures.door,
			"textures/validtex/doorr.xpm"))
		return (false);
	return (true);
}

int	get_tex_pixel(t_texture *tex, int x, int y)
{
	int	index;

	if (!tex || !tex->data || tex->line_length == 0)
		return (0);
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	index = y * (tex->line_length / 4) + x;
	return (tex->data[index]);
}

void	draw_void_column(t_game *game, int x)
{
	int	y;

	y = 0;
	while (y < game->window.height)
	{
		if (y < game->window.height / 2)
			draw_ceiling(game, x, y);
		else
			draw_floor(game, x, y);
		y++;
	}
}
