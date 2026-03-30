/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:22:46 by amabbadi          #+#    #+#             */
/*   Updated: 2025/03/27 16:22:46 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
/*anything when it comes to reading the file*/
int	read_file_lines(const char *filename, int *max_cols, int *rows)
{
	int		fd;
	char	*line;
	int		current_cols;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), -1);
	*max_cols = 0;
	*rows = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (process_line(line, &current_cols) == -1)
			return (free(line), close(fd), -1);
		if (current_cols > *max_cols)
			*max_cols = current_cols;
		free(line);
		(*rows)++;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	determine_dimensions_and_allocate(const char *filename, t_grid *map,
		int *max_cols, int *rows)
{
	if (read_file_lines(filename, max_cols, rows) == -1)
		return (-1);
	map->grid = allocate_grid(*max_cols, *rows);
	if (!map->grid)
		return (-1);
	return (0);
}

int	read_and_process_rows(const char *filename, t_grid *map)
{
	int		fd;
	char	*line;
	int		row;
	char	**tokens;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error opening file"), -1);
	row = 0;
	line = get_next_line(fd);
	while (line)
	{
		tokens = ft_split(line, ' ');
		if (!tokens)
			return (free(line), close(fd), -1);
		if (process_row(map, tokens, row) == -1)
			return (free(tokens), free(line), close(fd), -1);
		free(tokens);
		free(line);
		row++;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	populate_grid(const char *filename, t_grid *map)
{
	return (read_and_process_rows(filename, map));
}

int	read_map(const char *filename, t_grid *map)
{
	int	max_cols;
	int	rows;

	if (determine_dimensions_and_allocate(filename, map, \
		&max_cols, &rows) == -1)
		return (-1);
	if (populate_grid(filename, map) == -1)
		return (-1);
	map->width = max_cols;
	map->height = rows;
	return (0);
}
