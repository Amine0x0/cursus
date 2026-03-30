/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:08:10 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/02 16:19:00 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

static int	count_args(char **args)
{
	int	count;

	count = 0;
	if (args)
		while (args[count])
			count++;
	return (count);
}

static int	is_empty_unquoted_word(t_token *token)
{
	return (token->type == TOKEN_WORD && token->quoted == 0 && token->value
		&& ft_strlen(token->value) == 0);
}

static char	**copy_args(char **old_args, int count)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (count + 2));
	i = 0;
	if (!new_args)
		return (NULL);
	if (old_args)
	{
		while (i < count)
		{
			new_args[i] = old_args[i];
			i++;
		}
		free(old_args);
	}
	return (new_args);
}

int	add_argument(t_cmd *cmd, t_token *token)
{
	int		count;
	char	**new_args;

	if (!cmd || !token)
		return (0);
	if (is_empty_unquoted_word(token))
		return (1);
	count = count_args(cmd->args);
	new_args = copy_args(cmd->args, count);
	new_args[count] = ft_strdup(token->value);
	if (!new_args[count])
		return (free(new_args), 0);
	new_args[count + 1] = NULL;
	cmd->args = new_args;
	return (1);
}
