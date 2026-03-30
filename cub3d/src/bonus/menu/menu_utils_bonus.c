/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:30:00 by amabbadi          #+#    #+#             */
/*   Updated: 2026/01/18 18:35:01 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

static void	draw_art_line(t_game *game, char *line, int *pos, int center_x)
{
	int	len;

	len = (int)ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
		len--;
	}
	pos[0] = center_x - (len * 6) / 2;
	mlx_string_put(game->window.mlx, game->menu_window, pos[0], pos[1],
		0xFF0000, line);
	pos[1] += 15;
}

void	draw_menu_art(t_game *game)
{
	int		fd;
	char	*line;
	int		pos[2];
	int		center_x;

	fd = open("art/art.art", O_RDONLY);
	if (fd <= 0)
		return ;
	pos[1] = 100;
	center_x = game->menu_width / 2;
	line = get_next_line(fd);
	while (line)
	{
		draw_art_line(game, line, pos, center_x);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	cleanup_menu_resources(t_game *game)
{
	if (game->menu_window)
	{
		mlx_destroy_window(game->window.mlx, game->menu_window);
		game->menu_window = NULL;
	}
	if (game->screen.img)
	{
		mlx_destroy_image(game->window.mlx, game->screen.img);
		game->screen.img = NULL;
	}
}

static void	init_game_window(t_game *game)
{
	game->window.width = WINDOW_X;
	game->window.height = WINDOW_Y;
	game->window.win = mlx_new_window(game->window.mlx, game->window.width,
			game->window.height, game->window.title);
	if (!game->window.win || !init_screen(game))
	{
		log_event("Failed to initialize game screen", ERROR);
		exit_game(game, 1);
	}
	init_hand_sprite(game);
	mlx_mouse_hide(game->window.mlx, game->window.win);
	log_event("Mouse cursor hidden", INFO);
	setup_game_hooks(game);
}

void	handle_enter_key(t_game *game)
{
	print_terminal_welcome();
	game->in_menu = false;
	log_event("Starting game...", SUCCESS);
	init_keys_false(game);
	cleanup_menu_resources(game);
	init_game_window(game);
}
