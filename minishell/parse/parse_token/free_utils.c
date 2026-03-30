/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:07:55 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/02 16:07:56 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

static void	free_redirections(t_redirection *redirections)
{
	t_redirection	*current;
	t_redirection	*next;

	current = redirections;
	while (current)
	{
		next = current->next;
		if (!current)
			return ;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
}

static void	free_heredocs(t_heredoc *heredocs)
{
	t_heredoc	*current;
	t_heredoc	*next;

	current = heredocs;
	while (current)
	{
		next = current->next;
		if (current->delimiter)
			free(current->delimiter);
		if (current->fd != -1)
			close(current->fd);
		free(current);
		current = next;
	}
}

static void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free_redirections(cmd->redirections);
	free_heredocs(cmd->heredocs);
	free(cmd);
}

void	free_commands(t_cmd *commands)
{
	t_cmd	*current;
	t_cmd	*next;

	current = commands;
	while (current)
	{
		next = current->next;
		free_cmd(current);
		current = next;
	}
}
