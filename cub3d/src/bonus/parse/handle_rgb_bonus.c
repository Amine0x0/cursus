/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rgb_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 00:36:57 by maboulah          #+#    #+#             */
/*   Updated: 2026/01/15 19:37:54 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	is_line_valid(char **tokens)
{
	if (!(tokens && tokens[0] && tokens[1]))
		return (0);
	return (1);
}

int	ft_count_it(char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
			count++;
		i++;
	}
	return (count);
}

bool	handle_rgb_values(char **rgb, int **dst, char *found, int idx)
{
	int	i;

	i = 0;
	if (rgb && rgb[0] && rgb[1] && rgb[2])
	{
		*dst = malloc(sizeof(int) * 3);
		if (!*dst)
			return (0);
		(*dst)[0] = ft_atoi(rgb[0]);
		(*dst)[1] = ft_atoi(rgb[1]);
		(*dst)[2] = ft_atoi(rgb[2]);
		while (i < 3)
		{
			if ((*dst)[i] == -1)
			{
				free(*dst);
				*dst = NULL;
				return (0);
			}
			i++;
		}
		found[idx] = '1';
	}
	return (1);
}

bool	handle_color(char **tokens, t_game *game, char *found)
{
	char	**rgb;

	if (!tokens || !tokens[0] || !tokens[1])
		return (1);
	if (ft_count_it(tokens[1]) != 2)
		return (1);
	rgb = ft_split(tokens[1], ',');
	if (!rgb)
		return (0);
	if (!ft_strcmp(tokens[0], "F"))
	{
		if (!handle_rgb_values(rgb, &game->map.info.floor_color, found, 4))
			return (free_str_array(rgb), 0);
	}
	else if (!ft_strcmp(tokens[0], "C"))
	{
		if (!handle_rgb_values(rgb, &game->map.info.ceiling_color, found, 5))
		{
			free_str_array(rgb);
			return (0);
		}
	}
	free_str_array(rgb);
	return (1);
}
