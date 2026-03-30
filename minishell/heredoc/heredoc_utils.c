/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:13:15 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 17:26:47 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	create_pipe_if_needed(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

void	write_heredoc_line(int fd, char *line, t_heredoc_data *data)
{
	char	*line_to_write;

	if (!data->quoted)
	{
		line_to_write = expand_str(line, data->envp, data->exit_status);
		free(line);
	}
	else
	{
		line_to_write = line;
	}
	write(fd, line_to_write, ft_strlen(line_to_write));
	write(fd, "\n", 1);
	free(line_to_write);
}
