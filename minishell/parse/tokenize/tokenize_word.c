/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:07:40 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/04 17:33:17 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

static int	process_char_in_word(char c, int *i, char *word,
		t_word_state *state)
{
	if (handle_quotes(c, &state->in_quotes, &state->quote_char))
	{
		(*i)++;
		return (1);
	}
	if (!state->in_quotes && is_delimiter(c))
		return (0);
	word[state->word_pos++] = c;
	(*i)++;
	return (1);
}

static char	*finalize_word(char *word, t_word_state *state,
		char *final_quote_char)
{
	if (state->in_quotes)
	{
		print_error(NULL, "syntax error: unclosed quotes");
		free(word);
		return (NULL);
	}
	word[state->word_pos] = '\0';
	*final_quote_char = state->quote_char;
	return (word);
}

static char	*extract_word_content(char *input, int *i,
		char *final_quote_char)
{
	char			*word;
	t_word_state	state;

	state.word_pos = 0;
	state.in_quotes = 0;
	state.quote_char = 0;
	word = allocate_word_buffer(input);
	if (!word)
		return (NULL);
	while (input[*i])
	{
		if (!process_char_in_word(input[*i], i, word, &state))
			break ;
	}
	return (finalize_word(word, &state, final_quote_char));
}

static t_token	*create_word_token(char *word, char quote_char)
{
	t_token	*token;

	token = create_token(TOKEN_WORD, word);
	if (!token)
		return (NULL);
	if (quote_char == '\'')
		token->quoted = 1;
	else if (quote_char == '\"')
		token->quoted = 2;
	return (token);
}

t_token	*tokenize_word(char *input, int *i)
{
	char	*word;
	char	quote_char;
	t_token	*token;

	word = extract_word_content(input, i, &quote_char);
	if (!word)
		return (NULL);
	token = create_word_token(word, quote_char);
	free(word);
	if (!token)
	{
		print_error(NULL, "memory allocation failed");
		return (NULL);
	}
	return (token);
}
