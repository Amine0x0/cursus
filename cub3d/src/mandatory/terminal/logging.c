/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:55:25 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/31 09:46:39 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	log_event(const char *msg, t_log_type type)
{
	if (!msg)
		return ;
	printf("\033[33m[log]:\033[0m ");
	if (type == INFO)
		printf("\033[37m%s\033[0m\n", msg);
	else if (type == SUCCESS)
		printf("\033[32m%s\033[0m\n", msg);
	else if (type == ERROR)
		printf("\033[31m%s\033[0m\n", msg);
}

void	print_art(const char *path)
{
	int		fd;
	char	*line;

	if (!path)
		return ;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		log_event("Failed to open art file", ERROR);
		return ;
	}
	printf("\n\n\n");
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("\t\t\033[35m%s\033[0m", line);
		free(line);
		line = get_next_line(fd);
	}
	printf("\n\n\n");
	close(fd);
}

void	print_terminal_welcome_helper(const char **s)
{
	s[0] = "W - Move Forward";
	s[1] = "S - Move Backward";
	s[2] = "A - Move Left";
	s[3] = "D - Move Right";
	s[4] = "LEFT ARROW - Rotate Left";
	s[5] = "RIGHT ARROW - Rotate Right";
	s[6] = "ESC - Quit";
	s[7] = NULL;
}

void	print_terminal_welcome(void)
{
	const char	*controls[8];
	int			term_width;
	int			len;
	int			padding;
	int			i;

	print_terminal_welcome_helper(controls);
	term_width = 80;
	len = ft_strlen("WELCOME TO CUB3D");
	padding = (term_width - len) / 2;
	printf("\n%*s\033[36m%s\033[0m", padding + len, "", "WELCOME TO CUB3D");
	printf("\n%*s\033[36m%s\033[0m\n\n", padding + len, "", "----------------");
	i = 0;
	while (controls[i])
	{
		len = ft_strlen(controls[i]);
		printf("\033[35m%s\033[0m\n", controls[i]);
		i++;
	}
	printf("\n");
}
