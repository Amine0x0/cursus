/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 20:28:46 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 20:35:09 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	get_signal_status(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	if (sig == SIGINT)
		return (130);
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		return (131);
	}
	else
		return (128 + sig);
}

int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}

int	*create_pipes(int cmd_count)
{
	int	*pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int) * 2 * (cmd_count - 1));
	if (!pipes)
	{
		perror("minishell: malloc");
		return (NULL);
	}
	while (i < cmd_count - 1)
	{
		if (pipe(pipes + i * 2) == -1)
		{
			perror("minishell: pipe");
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

pid_t	*allocate_pids(int cmd_count)
{
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		perror("minishell: malloc");
	return (pids);
}
