/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapcheck_helper_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboulah <maboulah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 01:16:49 by maboulah          #+#    #+#             */
/*   Updated: 2026/01/12 19:25:12 by maboulah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

bool	find_start_position(char **padded, int rows, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (padded[i][j] != '\0')
		{
			if (padded[i][j] == 'S' || padded[i][j] == 'E'
				|| padded[i][j] == 'W' || padded[i][j] == 'N')
			{
				*x = i;
				*y = j;
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

static int	is_not_empty(const char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (1);
		line++;
	}
	return (0);
}

int	max_width(char **grid)
{
	int	max;
	int	i;
	int	len;

	max = 0;
	i = 0;
	while (grid[i])
	{
		len = ft_strlen(grid[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

void	calc_map_limits(char **grid, int *nums)
{
	int	k;
	int	l;

	k = 0;
	1 && (nums[2] = 0, nums[0] = 0, nums[1] = 0);
	while (grid[nums[0]])
	{
		if (is_not_empty(grid[nums[0]]))
			k++;
		nums[0]++;
		if (k == 6)
			break ;
	}
	if (!grid[nums[0]])
		return ;
	while (grid[nums[0]] && !is_not_empty(grid[nums[0]]))
		nums[0]++;
	l = nums[0];
	while (grid[l] && is_not_empty(grid[l]))
	{
		l++;
		nums[1]++;
	}
}

char	**copy_map_lines(char **grid, int *nums)
{
	char	**map_lines;

	map_lines = malloc(sizeof(char *) * (nums[1] + 1));
	if (!map_lines)
		return (NULL);
	while (grid[nums[0]] && is_not_empty(grid[nums[0]])
		&& ft_player(&grid[nums[0]]))
	{
		map_lines[nums[2]] = ft_strdup(grid[nums[0]]);
		if (!map_lines[nums[2]])
			return (free_map_grid(map_lines), NULL);
		nums[2]++;
		nums[0]++;
	}
	map_lines[nums[2]] = NULL;
	return (map_lines);
}
