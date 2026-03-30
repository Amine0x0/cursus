/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:22:29 by amabbadi          #+#    #+#             */
/*   Updated: 2025/03/27 16:22:30 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*main file checks before even loading anything , i made sure it
doesn't dereference anything before all the checks are done
so (pls) no segv*/
int	is_valid_input(char *line)
{
	int		i;
	char	*str;

	str = "0123456789abcdefABCDEFxX-,+\n ";
	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_strchr(str, line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_ext(char *file)
{
	int		len;
	char	*ext;
	int		i;

	len = ft_strlen(file);
	ext = ".fdf";
	i = 0;
	if (len < 4)
		return (-1);
	while (ext[i])
	{
		if (file[len - 4 + i] != ext[i])
			return (-1);
		i++;
	}
	return (0);
}

int	check_map_file(char *file)
{
	int		fd;
	char	*line;

	if (check_ext(file) == -1)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	line = get_next_line(fd);
	if (line == NULL || *line == '\n')
		return (close(fd), -1);
	while (line != NULL)
	{
		if (!is_valid_input(line) || *line == '\n')
			return (free(line), close(fd), -1);
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}
