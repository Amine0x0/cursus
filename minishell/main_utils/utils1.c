/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 03:51:13 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 04:04:41 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static void	update_shlvl(char **entry)
{
	int		shlvl;
	char	*num_str;
	char	*new_entry;

	shlvl = ft_atoi(*entry + 6);
	if (shlvl < 0)
		shlvl = 0;
	if (shlvl >= 1000)
	{
		print_err("minishell: warning: shell level too high, resetting to 1\n",
			NULL);
		shlvl = 1;
	}
	else
		shlvl++;
	num_str = ft_itoa(shlvl);
	if (!num_str)
		return ;
	new_entry = ft_strjoin("SHLVL=", num_str);
	free(num_str);
	if (!new_entry)
		return ;
	free(*entry);
	*entry = new_entry;
}

void	increment_shlvl(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
		{
			update_shlvl(&envp[i]);
			return ;
		}
		i++;
	}
}

t_token	*get_tokens(char *line)
{
	t_token	*tokens;

	tokens = tokenize(line);
	if (!tokens)
	{
		free(line);
		return (NULL);
	}
	return (tokens);
}

int	check_non_empty_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && current->type != TOKEN_EOF)
	{
		if (current->type == TOKEN_WORD && current->value)
			return (1);
		if (current->type != TOKEN_WORD)
			return (1);
		current = current->next;
	}
	return (0);
}

int	initialize_shell(char **envp, char ***my_envp)
{
	*my_envp = setup_environment(envp);
	if (!*my_envp)
	{
		print_err("minishell: failed to initialize environment\n", NULL);
		return (1);
	}
	return (0);
}
