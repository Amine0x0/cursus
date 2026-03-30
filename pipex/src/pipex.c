/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:45:27 by amabbadi          #+#    #+#             */
/*   Updated: 2025/03/22 16:45:28 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_cmd(char *cmd, char **envp, int in_fd, int out_fd)
{
	if (dup2(in_fd, STDIN_FILENO) == -1 || dup2(out_fd, STDOUT_FILENO) == -1)
		(perror("Dup error"), exit(1));
	(close(in_fd), close(out_fd));
	exec(cmd, envp);
	exit(1);
}

int	spawn_process(char **argv, char **envp, int *pipefd, int is_input)
{
	int		fd;
	pid_t	pid;

	if (is_input)
		fd = open(argv[1], O_RDONLY);
	else
		fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(NULL), -1);
	pid = fork();
	if (!pid)
	{
		if (is_input)
			(close(pipefd[0]), exec_cmd(argv[2], envp, fd, pipefd[1]));
		else
			(close(pipefd[1]), exec_cmd(argv[3], envp, pipefd[0], fd));
	}
	else if (pid < 0)
		return ((close(fd), close(pipefd[0]), close(pipefd[1])),
			perror("Fork error"), -1);
	close(fd);
	return (pid);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		status;
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		return (ft_printf("Usage: ./pipex <f1> <cmd1> <cmd2> <f2>\n"), 1);
	if (pipe(pipefd) == -1)
		return (perror("Pipe error"), 1);
	pid1 = spawn_process(argv, envp, pipefd, 1);
	if (pid1 == -1)
		(close(pipefd[0]), close(pipefd[1]));
	pid2 = spawn_process(argv, envp, pipefd, 0);
	if (pid2 == -1)
		(close(pipefd[0]), close(pipefd[1]));
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (pid2 == -1)
		return (1);
	return (WEXITSTATUS(status));
}
