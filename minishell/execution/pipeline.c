/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:49:47 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/12 21:03:54 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	handle_heredocs_and_signals(t_cmd *commands, char **envp,
		int exit_status)
{
	t_cmd	*current;

	current = commands;
	while (current)
	{
		if (current->heredocs)
		{
			if (handle_all_heredocs(current->heredocs, envp, exit_status) != 0)
				return (1);
		}
		current = current->next;
	}
	disable_parent_signals();
	return (0);
}

static int	setup_pipeline(int cmd_count, int **pipes,
		t_process_tracker *tracker)
{
	*pipes = create_pipes(cmd_count);
	if (!*pipes)
		return (1);
	tracker->pids = allocate_pids(cmd_count);
	if (!tracker->pids)
	{
		close_all_pipes(*pipes, 2 * (cmd_count - 1));
		free(*pipes);
		return (1);
	}
	tracker->count = cmd_count;
	return (0);
}

int	execute_pipeline(t_cmd *commands, char ***envp, int *exit_status)
{
	int						cmd_count;
	int						*pipes;
	t_process_tracker		tracker;
	int						result;
	t_launch_children_args	lc_args;

	cmd_count = count_commands(commands);
	if (cmd_count <= 1)
		return (exec_simple_command(commands, envp, *exit_status));
	if (handle_heredocs_and_signals(commands, *envp, *exit_status) != 0)
		return (1);
	if (setup_pipeline(cmd_count, &pipes, &tracker) != 0)
		return (restore_parent_signals(), 1);
	lc_args.commands = commands;
	lc_args.cmd_count = cmd_count;
	lc_args.pipes = pipes;
	lc_args.envp = envp;
	lc_args.tracker = &tracker;
	if (launch_children(&lc_args) != 0)
		return (free(tracker.pids), close_all_pipes(pipes, 2 \
	* (cmd_count - 1)), free(pipes), restore_parent_signals(), 1);
	close_all_pipes(pipes, 2 * (cmd_count - 1));
	result = wait_for_all_children(&tracker);
	return (restore_parent_signals(), free(tracker.pids), free(pipes), result);
}
