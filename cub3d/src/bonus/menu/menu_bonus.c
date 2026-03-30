/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 03:51:13 by maboulah          #+#    #+#             */
/*   Updated: 2026/01/13 21:24:39 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	init_menu_background(t_game *game)
{
	int	tex_width;
	int	tex_height;

	if (!game || !game->window.mlx)
		return (false);
	game->menu_bg.img = mlx_xpm_file_to_image(game->window.mlx,
			"textures/validtex/1336.xpm", &tex_width, &tex_height);
	if (!game->menu_bg.img)
		return (false);
	game->menu_width = 1280;
	game->menu_height = 720;
	return (true);
}

void	draw_menu(t_game *game)
{
	if (!game || !game->window.mlx || !game->menu_window || !game->screen.img)
		return ;
	simulate_menu_background(game);
	mlx_put_image_to_window(game->window.mlx, game->menu_window,
		game->screen.img, 0, 0);
	draw_menu_art(game);
	draw_menu_start_text(game);
}

void	draw_menu_start_text(t_game *game)
{
	char	*text;
	int		text_len;
	int		center_x;
	int		text_x;

	text = "PRESS ENTER TO START";
	text_len = ft_strlen(text);
	center_x = game->menu_width / 2;
	text_x = center_x - (text_len * 6) / 2;
	mlx_string_put(game->window.mlx, game->menu_window, text_x,
		game->menu_height / 2 + 50, 0xFFFFFF, text);
}

int	menu_key_handler(int keycode, t_game *game)
{
	if (!game)
		return (0);
	if (keycode == 65293 || keycode == 36)
	{
		handle_enter_key(game);
		return (0);
	}
	if (keycode == 65307)
	{
		log_event("Exiting from menu...", INFO);
		exit_game(game, 0);
	}
	return (0);
}
