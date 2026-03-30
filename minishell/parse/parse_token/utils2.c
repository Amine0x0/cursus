/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:09:57 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/02 16:19:09 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

t_cmd	*finale_validation(t_cmd *cmd_list)
{
	t_cmd	*last;

	if (!cmd_list)
		return (NULL);
	last = cmd_list;
	while (last->next)
		last = last->next;
	if (!last->args && !last->redirections && !last->heredocs)
	{
		free_commands(cmd_list);
		return (NULL);
	}
	return (cmd_list);
}

int	check_heredocs(t_cmd *current_cmd, t_token *current)
{
	t_heredoc	*hd;

	hd = current_cmd->heredocs;
	while (hd)
	{
		if (hd->delimiter && ft_strcmp(current->value, hd->delimiter) == 0)
			return (1);
		hd = hd->next;
	}
	if (add_argument(current_cmd, current))
		return (0);
	return (-1);
}

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirections = NULL;
	cmd->heredocs = NULL;
	cmd->next = NULL;
	return (cmd);
}
