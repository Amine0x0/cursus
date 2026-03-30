/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 01:40:58 by maboulah          #+#    #+#             */
/*   Updated: 2025/12/31 09:46:39 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	if (!dstsize)
		return (j);
	while (src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (j);
}

bool	ft_player(char **str)
{
	int		i;
	int		j;
	int		flag;
	char	s[9];

	i = 0;
	j = 0;
	flag = 0;
	ft_strlcpy(s, "10NSEW\n ", 9);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == 'W' || str[i][j] == 'E' || str[i][j] == 'S'
				|| str[i][j] == 'N')
				flag += 1;
			if (!ft_strchr(s, str[i][j]) || flag > 1)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static char	**pad_map_alloc(int padded_rows, int padded_width)
{
	char	**padded;
	int		i;
	int		j;

	padded = malloc(sizeof(char *) * (padded_rows + 1));
	if (!padded)
		return (NULL);
	i = 0;
	while (i < padded_rows)
	{
		padded[i] = malloc(sizeof(char) * (padded_width + 1));
		if (!padded[i])
		{
			while (--i >= 0)
				free(padded[i]);
			return (free(padded), NULL);
		}
		j = -1;
		while (j++ < padded_width)
			padded[i][j] = 'x';
		padded[i][padded_width] = '\0';
		i++;
	}
	return (padded);
}

static void	pad_map_copy(char **grid, char **padded, int rows)
{
	int		i;
	int		j;
	int		len;
	char	c;

	i = 0;
	while (i < rows)
	{
		len = ft_strlen(grid[i]);
		j = 0;
		while (j < len)
		{
			c = grid[i][j];
			if (c == ' ')
				c = 'x';
			if (grid[i][j] != '\n')
				padded[i + 1][j + 1] = c;
			j++;
		}
		i++;
	}
}

char	**pad_map(char **grid)
{
	int		rows;
	int		width;
	int		padded_width;
	int		padded_rows;
	char	**padded;

	rows = 0;
	while (grid[rows])
		rows++;
	width = max_width(grid);
	padded_width = width + 2;
	padded_rows = rows + 2;
	padded = pad_map_alloc(padded_rows, padded_width);
	if (!padded)
		return (NULL);
	pad_map_copy(grid, padded, rows);
	padded[padded_rows] = NULL;
	return (padded);
}
