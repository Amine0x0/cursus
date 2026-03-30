/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:07:26 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/04 17:15:41 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	check_redirection_syntax(t_token *current)
{
	if (!current->next || current->next->type == TOKEN_EOF)
		return (syntax_error("minishell: syntax error \
near unexpected token `newline'"));
	if (current->next->type == TOKEN_PIPE)
		return (syntax_error("minishell: syntax error \
near unexpected token `|'"));
	if (is_redirection(current->next->type))
	{
		if (current->next->type == TOKEN_REDIR_APPEND)
			return (syntax_error("minishell: syntax error \
near unexpected token `>>'"));
		else if (current->next->type == TOKEN_REDIR_OUT)
			return (syntax_error("minishell: syntax error \
near unexpected token `>'"));
		else if (current->next->type == TOKEN_REDIR_IN)
			return (syntax_error("minishell: syntax error \
near unexpected token `<'"));
		else if (current->next->type == TOKEN_HEREDOC)
			return (syntax_error("minishell: syntax error \
near unexpected token `<<'"));
	}
	return (1);
}

int	check_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;

	prev = NULL;
	current = tokens;
	if (!tokens)
		return (0);
	while (current && current->type != TOKEN_EOF)
	{
		if (current->type == TOKEN_PIPE && !prev)
			return (syntax_error("minishell: syntax error \
near unexpected token `|'"));
		if (current->type == TOKEN_PIPE && prev && prev->type == TOKEN_PIPE)
			return (syntax_error("minishell: syntax error \
near unexpected token `|'"));
		if (is_redirection(current->type))
			if (!check_redirection_syntax(current))
				return (0);
		prev = current;
		current = current->next;
	}
	if (prev && prev->type == TOKEN_PIPE)
		return (syntax_error("minishell: syntax error near \
unexpected token `|'"));
	return (1);
}
