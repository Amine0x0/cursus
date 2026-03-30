/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:49:42 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/12 21:03:50 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	execute_builtin_with_redirect(t_cmd *cmd, char ***envp)
{
	int		saved_stdin;
	int		saved_stdout;
	int		ret;
	char	*last_arg;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (setup_redirections(cmd) != 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	ret = execute_builtin(cmd->args, envp);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	last_arg = get_last_arg(cmd->args);
	if (last_arg)
		update_underscore_var(envp, last_arg);
	return (ret);
}

static int	execute_external_command(t_cmd *cmd, char ***envp)
{
	pid_t	pid;
	int		status;
	int		ret;
	char	*last_arg;

	disable_parent_signals();
	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), restore_parent_signals(), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (setup_redirections(cmd) != 0)
			exit(1);
		ret = exec_external_cmd(cmd, envp);
		exit(ret);
	}
	waitpid(pid, &status, 0);
	restore_parent_signals();
	ret = handle_signal_status(status);
	last_arg = get_last_arg(cmd->args);
	if (last_arg)
		update_underscore_var(envp, last_arg);
	return (ret);
}

static int	handle_redir_no_args(t_cmd *cmd, char ***envp, int exit_status)
{
	int	saved_stdout;
	int	saved_stdin;
	int	redir_result;

	if ((!cmd->args || !cmd->args[0]) && cmd->redirections)
	{
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		redir_result = apply_redirections(cmd->redirections, cmd->heredocs,
				*envp, exit_status);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
		if (redir_result)
			return (1);
		else
			return (0);
	}
	return (-1);
}

int	exec_simple_command(t_cmd *cmd, char ***envp, int exit_status)
{
	int	result;

	result = handle_redir_no_args(cmd, envp, exit_status);
	if (result != -1)
		return (result);
	result = handle_heredocs_check(cmd, *envp, exit_status);
	if (result != 0)
		return (result);
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (cmd->args[0][0] == '"' && cmd->args[0][1] == '"' \
	&& cmd->args[0][2] == '\0')
	{
		print_err("minishell: %s: command not found\n", cmd->args[0]);
		return (127);
	}
	if (is_builtin(cmd->args[0]))
		return (execute_builtin_with_redirect(cmd, envp));
	return (execute_external_command(cmd, envp));
}

int	exec_external_cmd(t_cmd *cmd, char ***envp)
{
	char	*path;
	int		error;
	char	*sh_argv[3];

	if (!cmd || !cmd->args || !cmd->args[0])
		return (127);
	path = find_command_path(cmd->args[0], *envp);
	error = handle_path_errors(path, cmd->args[0]);
	if (error != 0)
		return (error);
	error = handle_file_checks(path, cmd->args[0]);
	if (error != 0)
		return (error);
	execve(path, cmd->args, *envp);
	if (errno == ENOEXEC)
	{
		sh_argv[0] = "sh";
		sh_argv[1] = path;
		sh_argv[2] = NULL;
		execve("/bin/sh", sh_argv, *envp);
	}
	perror("minishell: execve");
	free(path);
	return (126);
}
