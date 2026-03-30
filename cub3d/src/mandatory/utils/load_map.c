/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:55:22 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/31 09:46:39 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	count_lines_in_file(char *path)
{
	int		fd;
	char	*line;
	int		count;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static bool	alloc_map(t_game *game, int lines)
{
	game->map.height = lines;
	game->map.firstmap = malloc(sizeof(char *) * (lines + 1));
	if (!game->map.firstmap)
		return (false);
	return (true);
}

static bool	load_map_lines(t_game *game, char *path)
{
	int		fd;
	int		i;
	char	*line;
	int		len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	i = 0;
	game->map.width = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->map.firstmap[i] = line;
		len = (int)ft_strlen(line);
		if (len > game->map.width)
			game->map.width = len;
		i++;
		line = get_next_line(fd);
	}
	game->map.firstmap[i] = NULL;
	close(fd);
	return (true);
}

bool	load_map(t_game *game, char *path)
{
	int	lines;

	if (!game || !path)
		return (false);
	lines = count_lines_in_file(path);
	if (lines <= 0)
		return (false);
	if (!alloc_map(game, lines))
		return (false);
	if (!load_map_lines(game, path))
	{
		free(game->map.firstmap);
		game->map.firstmap = NULL;
		return (false);
	}
	return (true);
}
