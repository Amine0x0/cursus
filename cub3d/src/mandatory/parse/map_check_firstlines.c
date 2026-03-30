/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_firstlines.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulah <maboulah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 00:20:10 by maboulah          #+#    #+#             */
/*   Updated: 2025/12/27 18:59:48 by maboulah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	flag(char *av)
{
	int	j;

	j = 0;
	while (av[j])
	{
		if (av[j] != ' ' && av[j] != '\n')
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strdup_new_line(const char *s)
{
	size_t	len;
	char	*dup;
	size_t	i;

	len = ft_strlen(s);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

bool	is_exist(char **text, t_game *game)
{
	char	*line;
	char	**tokens;
	char	found[7];
	int		i;

	i = 0;
	ft_strlcpy(found, "000000", 7);
	while (text[i])
	{
		line = strim(text[i], 0);
		if (!line)
			return (false);
		tokens = ft_split(line, ' ');
		free(line);
		if (!handle_color(tokens, game, found) || !is_line_valid(tokens)
			|| tokens[2])
		{
			free_str_array(tokens);
			return (false);
		}
		handle_texture(tokens, game, found);
		free_str_array(tokens);
		i++;
	}
	return (check_it(found));
}

static bool	fill_text_array(char **text, t_game *game, int *count)
{
	int	i;

	i = 0;
	while (game->map.firstmap[i] && *count < 6)
	{
		if (flag(game->map.firstmap[i]))
		{
			text[*count] = ft_strdup_new_line(game->map.firstmap[i]);
			if (!text[*count])
			{
				free_str_array(text);
				return (false);
			}
			(*count)++;
		}
		i++;
	}
	return (true);
}

bool	check_text(t_game *game)
{
	char	**text;
	int		count;
	bool	result;

	text = malloc(sizeof(char *) * 7);
	count = 0;
	if (!text)
		return (false);
	if (!fill_text_array(text, game, &count))
		return (false);
	text[count] = NULL;
	result = is_exist(text, game);
	free_str_array(text);
	return (result);
}
