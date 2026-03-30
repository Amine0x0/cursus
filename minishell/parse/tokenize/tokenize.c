/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:07:46 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/03 10:03:10 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

static t_token	*handle_brace(char *input, int *i)
{
	char	c;

	c = input[*i];
	if (c == '{')
	{
		print_err(" unexpected end of file\n", NULL);
		return (NULL);
	}
	else if (c == '}')
	{
		print_err("minishell: syntax error near unexpected token `}'\n", NULL);
		return (NULL);
	}
	return (NULL);
}

static t_token	*handle_output_redirection(char *input, int *i)
{
	if (input[*i + 1] == '>' && input[*i + 2] == '>')
	{
		print_err("minishell: syntax error near unexpected token `>'\n", NULL);
		return (NULL);
	}
	else if (input[*i + 1] == '>')
	{
		*i += 2;
		return (create_token(TOKEN_REDIR_APPEND, ">>"));
	}
	else
	{
		(*i)++;
		return (create_token(TOKEN_REDIR_OUT, ">"));
	}
}

static t_token	*handle_input_redirection(char *input, int *i)
{
	if (input[*i + 1] == '<' && input[*i + 2] == '<')
	{
		print_err("minishell: syntax error near unexpected token `<'\n", NULL);
		return (NULL);
	}
	else if (input[*i + 1] == '<')
	{
		*i += 2;
		return (create_token(TOKEN_HEREDOC, "<<"));
	}
	else
	{
		(*i)++;
		return (create_token(TOKEN_REDIR_IN, "<"));
	}
}

static t_token	*process_character(char *input, int *i)
{
	char	c;

	c = input[*i];
	if (c == '|')
	{
		(*i)++;
		return (create_token(TOKEN_PIPE, "|"));
	}
	else if (c == '<')
		return (handle_input_redirection(input, i));
	else if (c == '>')
		return (handle_output_redirection(input, i));
	else if (c == '{' || c == '}')
		return (handle_brace(input, i));
	else
		return (tokenize_word(input, i));
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	t_token	*current;
	int		i;

	i = 0;
	head = NULL;
	while (input[i])
	{
		while (input[i] && is_whitespace(input[i]))
			i++;
		if (!input[i])
			break ;
		current = process_character(input, &i);
		if (!current)
		{
			free_tokens(head);
			return (NULL);
		}
		add_token_to_list(&head, current);
	}
	current = create_token(TOKEN_EOF, "");
	if (current)
		add_token_to_list(&head, current);
	return (head);
}
