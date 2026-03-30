/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 23:28:55 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/08 23:28:57 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

static void	cleanup_add_failure(char **new_env, char *key, char *value)
{
	if (new_env)
		free_env(new_env);
	if (key)
		free(key);
	if (value)
		free(value);
}

static int	validate_key_value(char *key, char *value)
{
	if (!key || !*key)
	{
		free(key);
		if (value)
			free(value);
		return (0);
	}
	return (1);
}

static char	**allocate_and_copy_env(char ***envp, int count)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		print_err("minishell: export: cannot allocate memory\n", NULL);
		return (NULL);
	}
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup((*envp)[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	return (new_env);
}

static char	**create_env_with_new_var(char ***envp, char *key, char *value,
		int has_equal)
{
	int		count;
	char	**new_env;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = allocate_and_copy_env(envp, count);
	if (!new_env)
		return (NULL);
	new_env[count] = create_env_entry(key, value, has_equal);
	if (!new_env[count])
	{
		cleanup_add_failure(new_env, key, value);
		return (NULL);
	}
	new_env[count + 1] = NULL;
	return (new_env);
}

void	add_new_var(char ***envp, char *key, char *value, int has_equal)
{
	char	**new_env;

	if (!validate_key_value(key, value))
	{
		free(key);
		free(value);
		return ;
	}
	new_env = create_env_with_new_var(envp, key, value, has_equal);
	if (!new_env)
		return ;
	replace_env_array(envp, new_env);
	free(key);
	free(value);
}
