/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:49:50 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/11 23:53:16 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	is_ambiguous_redirection(const char *file)
{
	int	all_space;
	int	i;

	i = 0;
	all_space = 1;
	if (file == NULL)
		return (1);
	while (file[i])
	{
		if (!ft_isspace((unsigned char)file[i]))
			all_space = 0;
		++i;
	}
	if (all_space)
		return (1);
	if (ft_strchr(file, '$'))
		return (1);
	return (0);
}

static int	handle_input_redirection(t_redirection *redir)
{
	int	fd;

	if (is_ambiguous_redirection(redir->file))
	{
		print_err("minishell: ambiguous redirect\n", NULL);
		return (1);
	}
	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		if (errno == ENOENT)
			print_err(
				"minishell: %s: No such \
file or directory\n",
				redir->file);
		else if (errno == EACCES)
			print_err(
				"minishell: %s: Permission \
denied\n",
				redir->file);
		else
			perror("minishell");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	handle_output_redirection(t_redirection *redir, int *last_out_fd,
		int *any_out)
{
	int	fd;

	if (is_ambiguous_redirection(redir->file))
		return (print_err("minishell: ambiguous redirect\n", NULL), 1);
	if (*last_out_fd != -1)
		close(*last_out_fd);
	if (redir->type == TOKEN_REDIR_OUT)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		if (errno == EACCES)
			print_err(
				"minishell: %s: Permission \
denied\n",
				redir->file);
		else
			perror("minishell");
		return (1);
	}
	*last_out_fd = fd;
	*any_out = 1;
	return (0);
}

int	setup_redirections(t_cmd *cmd)
{
	t_redirection	*redir;
	int				last_out_fd;
	int				any_out;

	last_out_fd = -1;
	any_out = 0;
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN && handle_input_redirection(redir))
			return (1);
		else if ((redir->type == TOKEN_REDIR_OUT
				|| redir->type == TOKEN_REDIR_APPEND)
			&& handle_output_redirection(redir, &last_out_fd, &any_out))
			return (1);
		redir = redir->next;
	}
	if (any_out && last_out_fd != -1)
	{
		dup2(last_out_fd, STDOUT_FILENO);
		close(last_out_fd);
	}
	apply_heredocs(cmd->heredocs);
	return (0);
}

int	apply_redirections(t_redirection *redirections, t_heredoc *heredocs,
		char **envp, int exit_status)
{
	t_cmd	temp_cmd;

	(void)envp;
	(void)exit_status;
	ft_memset(&temp_cmd, 0, sizeof(temp_cmd));
	temp_cmd.redirections = redirections;
	temp_cmd.heredocs = heredocs;
	return (setup_redirections(&temp_cmd));
}
