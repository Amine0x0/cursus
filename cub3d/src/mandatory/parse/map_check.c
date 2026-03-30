/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulah <maboulah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 00:45:26 by maboulah          #+#    #+#             */
/*   Updated: 2026/01/12 19:24:41 by maboulah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**extract_map_lines(char **grid)
{
	int	nums[3];

	if (!grid)
		return (NULL);
	calc_map_limits(grid, nums);
	return (copy_map_lines(grid, nums));
}

bool	extract_and_pad(t_game *game, char ***map_lines, char ***padded)
{
	int	i;

	i = -1;
	*map_lines = extract_map_lines(game->map.firstmap);
	if (!*map_lines)
		return (false);
	*padded = pad_map(*map_lines);
	if (!*padded)
		return (false);
	if (map_lines && *map_lines)
	{
		while ((*map_lines)[++i])
			free((*map_lines)[i]);
		free(*map_lines);
		*map_lines = NULL;
	}
	return (true);
}

bool	allocate_grid(char ***grid, char **padded, int rows)
{
	int	i;

	*grid = malloc(sizeof(char *) * (rows + 1));
	if (!*grid)
		return (false);
	i = 0;
	while (i < rows)
	{
		(*grid)[i] = ft_strdup(padded[i]);
		if (!(*grid)[i])
		{
			while (--i >= 0)
				free((*grid)[i]);
			free(*grid);
			return (false);
		}
		i++;
	}
	(*grid)[rows] = NULL;
	return (true);
}

static bool	setup_map_dimensions(t_game *game, char **padded, int *start)
{
	start[2] = 0;
	while (padded[start[2]])
		start[2]++;
	start[3] = ft_strlen(padded[0]);
	game->map.height = start[2];
	game->map.width = start[3];
	return (true);
}

bool	check_map1(t_game *game)
{
	char				**map_lines;
	char				**padded;
	int					start[4];
	bool				flodfil;
	t_flood_fill_params	params;

	start[0] = -1;
	start[1] = -1;
	if (!extract_and_pad(game, &map_lines, &padded))
		return (false);
	setup_map_dimensions(game, padded, start);
	if (!find_start_position(padded, start[2], &start[0], &start[1])
		|| !allocate_grid(&game->map.grid, padded, start[2]))
	{
		free_str_array(padded);
		free_str_array(map_lines);
		return (false);
	}
	params.height = start[2];
	params.width = start[3];
	flodfil = flood_fill(padded, start[0], start[1], params);
	free_str_array(padded);
	return (flodfil);
}
