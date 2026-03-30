/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 00:24:06 by maboulah          #+#    #+#             */
/*   Updated: 2025/12/31 09:46:38 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_it(char *found)
{
	int	k;

	k = 0;
	while (found[k])
	{
		if (found[k] == '0' && k <= 3)
			return (false);
		if (found[k] == '0')
			return (false);
		k++;
	}
	return (true);
}

char	*strim(char *s, int offset)
{
	int		i;
	int		j;
	int		len;
	char	*out;

	i = 0;
	while (s[i] == ' ')
		i++;
	i += offset;
	while (s[i] == ' ')
		i++;
	len = ft_strlen(&s[i]);
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	j = 0;
	while (s[i])
	{
		out[j] = s[i];
		i++;
		j++;
	}
	out[j] = '\0';
	return (out);
}

bool	ft_open(char *last)
{
	int	fd;

	fd = open(last, O_RDONLY);
	if (fd == -1)
	{
		return (false);
	}
	close(fd);
	return (true);
}

static bool	set_texture(char **dst, char *path)
{
	if (!ft_open(path))
		return (false);
	if (*dst)
		free(*dst);
	*dst = ft_strdup(path);
	return (true);
}

void	handle_texture(char **tokens, t_game *game, char *found)
{
	if (!ft_strcmp(tokens[0], "NO"))
	{
		if (set_texture(&game->map.info.no_texture, tokens[1]))
			found[0] = '1';
	}
	else if (!ft_strcmp(tokens[0], "SO"))
	{
		if (set_texture(&game->map.info.so_texture, tokens[1]))
			found[1] = '1';
	}
	else if (!ft_strcmp(tokens[0], "WE"))
	{
		if (set_texture(&game->map.info.we_texture, tokens[1]))
			found[2] = '1';
	}
	else if (!ft_strcmp(tokens[0], "EA"))
	{
		if (set_texture(&game->map.info.ea_texture, tokens[1]))
			found[3] = '1';
	}
}
