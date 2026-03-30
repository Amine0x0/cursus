/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:08:05 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/03 07:14:35 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

static t_cmd	*handle_pipe_error(t_cmd *cmd_list)
{
	print_err("minishell: syntax error near unexpected token `|'\n", NULL);
	free_commands(cmd_list);
	return (NULL);
}

static t_cmd	*create_new_pipe_cmd(t_cmd **current_cmd, t_cmd *cmd_list)
{
	(*current_cmd)->next = init_cmd();
	if (!(*current_cmd)->next)
		return (free_commands(cmd_list), NULL);
	*current_cmd = (*current_cmd)->next;
	return (cmd_list);
}

static int	process_token(t_cmd *current_cmd, t_token **current)
{
	if (is_redirection((*current)->type))
		return (handle_redirection(current_cmd, current));
	else if ((*current)->type == TOKEN_WORD)
	{
		if (check_heredocs(current_cmd, *current) == -1)
			return (0);
		*current = (*current)->next;
	}
	else
		*current = (*current)->next;
	return (1);
}

static t_cmd	*init_first_cmd(t_cmd **cmd_list, t_cmd **current_cmd)
{
	*cmd_list = init_cmd();
	*current_cmd = *cmd_list;
	return (*cmd_list);
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_token	*current;

	cmd_list = NULL;
	current_cmd = NULL;
	current = tokens;
	while (current && current->type != TOKEN_EOF)
	{
		if (!cmd_list && !init_first_cmd(&cmd_list, &current_cmd))
			return (NULL);
		else if (current->type == TOKEN_PIPE)
		{
			if (!current->next || current->next->type == TOKEN_PIPE)
				return (handle_pipe_error(cmd_list));
			if (!create_new_pipe_cmd(&current_cmd, cmd_list))
				return (NULL);
			current = current->next;
			continue ;
		}
		if (!process_token(current_cmd, &current))
			return (free_commands(cmd_list), NULL);
	}
	return (finale_validation(cmd_list));
}
