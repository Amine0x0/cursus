/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:07:49 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/02 16:26:44 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_delimiter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '<'
		|| c == '>' || c == '\0');
}

int	handle_quotes(char c, int *in_quotes, char *quote_char)
{
	if (!*in_quotes && (c == '\'' || c == '"'))
	{
		*in_quotes = 1;
		*quote_char = c;
		return (1);
	}
	else if (*in_quotes && c == *quote_char)
	{
		*in_quotes = 0;
		return (1);
	}
	return (0);
}

char	*allocate_word_buffer(char *input)
{
	char	*word;

	word = malloc(ft_strlen(input) + 1);
	if (!word)
		print_error(NULL, "memory allocation failed");
	return (word);
}
