/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:11:28 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/12 02:59:34 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static void	heredoc_child_process(int write_fd, char *delimiter,
		t_heredoc_data *data)
{
	char	*line;

	rl_catch_signals = 1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(write_fd);
			exit(0);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			close(write_fd);
			exit(0);
		}
		write_heredoc_line(write_fd, line, data);
	}
}

static int	handle_heredoc_parent(int pipefd[2], pid_t pid)
{
	int	status;
	int	sig;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	rl_catch_signals = 0;
	msh_signals();
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			return (close(pipefd[0]), -2);
		}
	}
	return (pipefd[0]);
}

static int	handle_heredoc(char *delimiter, int quoted, char **envp,
		int exit_status)
{
	int				pipefd[2];
	pid_t			pid;
	t_heredoc_data	data;

	data.envp = envp;
	data.exit_status = exit_status;
	data.quoted = quoted;
	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_child_process(pipefd[1], delimiter, &data);
		exit(0);
	}
	else if (pid > 0)
		return (handle_heredoc_parent(pipefd, pid));
	else
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), -1);
}

static void	update_last_heredoc_fd(t_heredoc *heredocs, int last_fd)
{
	t_heredoc	*last;

	if (last_fd == -1)
		return ;
	last = heredocs;
	while (last && last->next)
		last = last->next;
	if (last)
		last->fd = last_fd;
}

int	handle_all_heredocs(t_heredoc *heredocs, char **envp, int exit_status)
{
	t_heredoc	*current;
	int			last_fd;

	last_fd = -1;
	current = heredocs;
	while (current)
	{
		current->fd = handle_heredoc(current->delimiter, current->quoted, envp,
				exit_status);
		if (current->fd == -2 || current->fd == -1)
		{
			if (last_fd != -1)
				close(last_fd);
			return (current->fd);
		}
		if (last_fd != -1)
			close(last_fd);
		last_fd = current->fd;
		current = current->next;
	}
	update_last_heredoc_fd(heredocs, last_fd);
	return (0);
}
