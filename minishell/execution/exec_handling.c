/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:11:01 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 21:14:04 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	handle_heredocs_check(t_cmd *cmd, char **envp, int exit_status)
{
	int	heredoc_result;

	if (cmd && cmd->heredocs)
	{
		heredoc_result = handle_all_heredocs(cmd->heredocs, envp, exit_status);
		if (heredoc_result == -2)
			return (130);
		if (heredoc_result != 0)
			return (1);
	}
	return (0);
}

int	handle_signal_status(int status)
{
	int	sig;
	int	ret;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			ret = 130;
		else if (sig == SIGQUIT)
		{
			write(1, "Quit: 3\n", 8);
			ret = 131;
		}
		else
			ret = 128 + sig;
	}
	else
	{
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		else
			ret = 1;
	}
	return (ret);
}

int	handle_path_errors(char *path, char *cmd_name)
{
	if (!path)
	{
		if (ft_strchr(cmd_name, '/'))
			print_err("minishell: %s: No such file or directory\n",
				cmd_name);
		else
			print_err("minishell: %s: command not found\n", cmd_name);
		return (127);
	}
	return (0);
}

int	handle_file_checks(char *path, char *cmd_name)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_err("minishell: %s: is a directory\n", cmd_name);
		free(path);
		return (126);
	}
	if (access(path, X_OK) != 0)
	{
		print_err("minishell: %s: Permission denied\n", cmd_name);
		free(path);
		return (126);
	}
	return (0);
}
