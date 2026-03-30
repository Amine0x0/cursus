/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 21:07:40 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 21:07:41 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	wait_for_all_children(t_process_tracker *tracker)
{
	int	last_status;
	int	status;
	int	i;

	last_status = 0;
	i = 0;
	while (i < tracker->count)
	{
		waitpid(tracker->pids[i], &status, 0);
		if (i == tracker->count - 1)
		{
			if (WIFSIGNALED(status))
				last_status = get_signal_status(status);
			else
				last_status = get_exit_status(status);
		}
		i++;
	}
	return (last_status);
}

void	handle_child_process(t_child_process_args *args)
{
	int	ret;

	if (args->cmd_index > 0)
		dup2(args->pipes[(args->cmd_index - 1) * 2], STDIN_FILENO);
	if (args->cmd_index < args->cmd_count - 1)
		dup2(args->pipes[args->cmd_index * 2 + 1], STDOUT_FILENO);
	close_all_pipes(args->pipes, 2 * (args->cmd_count - 1));
	if (setup_redirections(args->cmd) != 0)
		exit(1);
	if (!args->cmd->args || \
!args->cmd->args[0] || args->cmd->args[0][0] == '\0')
	{
		print_err("minishell: : command not found\n", NULL);
		exit(127);
	}
	if (is_builtin(args->cmd->args[0]))
		ret = execute_builtin(args->cmd->args, args->envp);
	else
		ret = exec_external_cmd(args->cmd, args->envp);
	exit(ret);
}

void	run_child(t_cmd *current, t_launch_children_args *args, int i)
{
	t_child_process_args	child_args;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_args.cmd = current;
	child_args.cmd_index = i;
	child_args.cmd_count = args->cmd_count;
	child_args.pipes = args->pipes;
	child_args.envp = args->envp;
	handle_child_process(&child_args);
}

int	launch_children(t_launch_children_args *args)
{
	t_cmd	*current;
	int		i;
	int		j;

	current = args->commands;
	i = 0;
	while (i < args->cmd_count)
	{
		args->tracker->pids[i] = fork();
		if (args->tracker->pids[i] == -1)
		{
			perror("minishell: fork");
			j = 0;
			while (j < i)
				kill(args->tracker->pids[j++], SIGTERM);
			return (1);
		}
		if (args->tracker->pids[i] == 0)
			run_child(current, args, i);
		current = current->next;
		i++;
	}
	return (0);
}
