/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:29 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/13 21:23:55 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	load_sprite(t_game *game, t_sprite *sprite, char *path)
{
	if (!game || !sprite || !path || !game->window.mlx)
		return (false);
	sprite->texture.img = mlx_xpm_file_to_image(game->window.mlx, path,
			&sprite->texture.width, &sprite->texture.height);
	if (!sprite->texture.img)
	{
		log_event("Failed to load sprite", ERROR);
		return (sprite->loaded = false, false);
	}
	sprite->texture.data = (int *)mlx_get_data_addr(sprite->texture.img,
			&sprite->texture.bpp, &sprite->texture.line_length,
			&sprite->texture.endian);
	if (!sprite->texture.data)
	{
		log_event("Failed to get sprite data", ERROR);
		sprite->loaded = false;
		return (false);
	}
	sprite->width = sprite->texture.width;
	sprite->height = sprite->texture.height;
	sprite->loaded = true;
	log_event("Sprite loaded successfully", SUCCESS);
	return (true);
}

void	draw_sprite(t_game *game, t_sprite *sprite)
{
	t_sprite_params	params;

	if (!game || !sprite || !sprite->loaded || !sprite->texture.img
		|| !sprite->texture.data || !game->screen.data)
		return ;
	params.start_x = sprite->screen_x;
	params.start_y = sprite->screen_y;
	params.y = 0;
	while (params.y < sprite->height)
	{
		params.x = 0;
		while (params.x < sprite->width)
		{
			draw_sprite_pixel(game, sprite, &params);
			params.x++;
		}
		params.y++;
	}
}

void	draw_sprite_pixel(t_game *game, t_sprite *sprite, t_sprite_params *p)
{
	t_pixel	pix;

	pix.screen_x = p->start_x + p->x;
	pix.screen_y = p->start_y + p->y;
	if (pix.screen_x < 0 || pix.screen_x >= game->window.width
		|| pix.screen_y < 0 || pix.screen_y >= game->window.height)
		return ;
	pix.tex_x = (p->x * sprite->texture.width) / sprite->width;
	pix.tex_y = (p->y * sprite->texture.height) / sprite->height;
	if (pix.tex_x < 0 || pix.tex_x >= sprite->texture.width || pix.tex_y < 0
		|| pix.tex_y >= sprite->texture.height)
		return ;
	pix.tex_idx = pix.tex_y * sprite->texture.width + pix.tex_x;
	pix.color = sprite->texture.data[pix.tex_idx];
	if (pix.color != 0xFF00FF && (pix.color & 0x00FFFFFF) != 0)
	{
		pix.screen_idx = pix.screen_y * game->window.width + pix.screen_x;
		game->screen.data[pix.screen_idx] = pix.color;
	}
}

void	init_hand_sprite(t_game *game)
{
	float	scale_factor;
	int		x;
	int		y;

	if (!game)
		return ;
	if (!load_sprite(game, &game->hands, "textures/random/guns.xpm"))
	{
		log_event("Hand sprite not found, continuing without it", INFO);
		return ;
	}
	scale_factor = 0.5;
	game->hands.width = (int)(game->hands.texture.width * scale_factor);
	game->hands.height = (int)(game->hands.texture.height * scale_factor);
	x = (game->window.width - game->hands.width) / 2;
	y = game->window.height - game->hands.height - 0;
	game->hands.base_x = x;
	game->hands.base_y = y;
	game->hands.screen_x = x;
	game->hands.screen_y = y;
	game->hands.bob_timer = 0.0;
	log_event("Hand sprite scaled and centered on screen", SUCCESS);
}
