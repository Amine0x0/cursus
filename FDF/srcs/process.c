/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:57:37 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/05 16:57:38 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*anything related to the tokens themselves*/
int	process_token(char *token, t_coordinates *point)
{
	char	*comma;

	comma = ft_strchr(token, ',');
	if (comma)
	{
		*comma = '\0';
		point->z = ft_atoi(token);
		if (ft_strncmp(comma + 1, "0x", 2) == 0)
			point->color = ft_atoi_base(comma + 3, BASE_16);
		else
			point->color = ft_atoi_base(comma + 1, BASE_16);
	}
	else
	{
		point->z = ft_atoi(token);
		point->color = DEFAULT_COLOR;
	}
	return (0);
}

int	process_line(char *line, int *current_cols)
{
	char	**tokens;
	int		i;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (-1);
	*current_cols = 0;
	while (tokens[*current_cols])
		(*current_cols)++;
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return (0);
}

int	process_row(t_grid *map, char **tokens, int row)
{
	int	col;

	col = 0;
	while (tokens[col])
	{
		map->grid[row][col].x = col;
		map->grid[row][col].y = row;
		if (process_token(tokens[col], &map->grid[row][col]) == -1)
		{
			free(tokens[col]);
			return (-1);
		}
		free(tokens[col]);
		col++;
	}
	return (0);
}
