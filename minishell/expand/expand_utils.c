/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:58:44 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 14:46:12 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*expand_str(char *str, char **envp, int exit_status)
{
	int		i;
	char	*result;
	char	*tmp;
	char	*part;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
			part = expand_var(str, &i, envp, exit_status);
		else
			part = ft_substr(str, i++, 1);
		if (!part)
			return (free(result), NULL);
		tmp = ft_strjoin(result, part);
		(free(result), free(part));
		if (!tmp)
			return (NULL);
		result = tmp;
	}
	return (result);
}

int	should_split_word(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

t_token	*create_single_token(char *word)
{
	t_token	*token;

	if (!word || word[0] == '\0')
		return (create_token(TOKEN_WORD, ft_strdup("")));
	token = create_token(TOKEN_WORD, ft_strdup(word));
	if (token)
		token->quoted = 0;
	return (token);
}

void	free_words(char **words)
{
	int	i;

	i = 0;
	while (words && words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

t_token	*create_word_tokens(char *expanded_value)
{
	char	**words;
	t_token	*first;
	t_token	*last;
	int		i;
	t_token	*new_token;

	first = NULL;
	last = NULL;
	i = 0;
	words = ft_split(expanded_value, ' ');
	if (!words)
		return (create_token(TOKEN_WORD, ft_strdup("")));
	while (words[i])
	{
		new_token = create_single_token(words[i]);
		if (!new_token)
			return (free_words(words + i), free_tokens(first), NULL);
		add_token(&first, &last, new_token);
		free(words[i]);
		i++;
	}
	free(words);
	if (!first)
		return (create_token(TOKEN_WORD, ft_strdup("")));
	return (first);
}
