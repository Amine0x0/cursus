/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:27:46 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/04 14:46:14 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static void	handle_new_tokens(t_token *current, t_token *new_tokens)
{
	t_token	*last_new;

	last_new = new_tokens;
	while (last_new->next)
		last_new = last_new->next;
	last_new->next = current->next;
	free(current->value);
	current->value = new_tokens->value;
	current->quoted = new_tokens->quoted;
	if (new_tokens->next)
		current->next = new_tokens->next;
	new_tokens->value = NULL;
	new_tokens->next = NULL;
	free_tokens(new_tokens);
}

static void	process_split_expansion(t_token *current, char **envp,
		int exit_status)
{
	char	*expanded;
	t_token	*new_tokens;

	expanded = expand_str(current->value, envp, exit_status);
	if (current->quoted == 0 && should_split_word(expanded))
	{
		new_tokens = create_word_tokens(expanded);
		if (new_tokens)
			handle_new_tokens(current, new_tokens);
		else
		{
			free(current->value);
			current->value = ft_strdup("");
		}
		free(expanded);
	}
	else
	{
		free(current->value);
		if (expanded)
			current->value = expanded;
		else
			current->value = ft_strdup("");
	}
}

void	add_token(t_token **first, t_token **last, t_token *new_token)
{
	if (!*first)
		*first = new_token;
	else
		(*last)->next = new_token;
	*last = new_token;
}

static void	process_token_expansion(t_token *current, t_token *prev,
		char **envp, int exit_status)
{
	char	*expanded;

	if (current->type == TOKEN_WORD)
	{
		if (prev && prev->type == TOKEN_HEREDOC)
			return ;
		else if (current->quoted == 1)
		{
			expanded = ft_strdup(current->value);
			if (expanded)
			{
				free(current->value);
				current->value = expanded;
			}
		}
		else
			process_split_expansion(current, envp, exit_status);
	}
}

void	expand_tokens(t_token *tokens, char **envp, int exit_status)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next_token;

	current = tokens;
	prev = NULL;
	while (current)
	{
		next_token = current->next;
		process_token_expansion(current, prev, envp, exit_status);
		prev = current;
		current = next_token;
	}
}
