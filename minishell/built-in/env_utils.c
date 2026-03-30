/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:34:51 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/05 04:20:11 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	set_env_var_cd(char ***envp, char *name, char *value)
{
	char	*new_entry;

	new_entry = create_env_entry_basic(name, value);
	if (!new_entry)
		return (1);
	if (update_if_exists(envp, name, new_entry))
		return (0);
	if (append_new_entry(envp, new_entry))
	{
		free(new_entry);
		return (1);
	}
	return (0);
}

static int	env_var_exists(char ***envp, const char *key, size_t key_len)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, key_len) == 0
			&& ((*envp)[i][key_len] == '=' || (*envp)[i][key_len] == '\0'))
			return (1);
		i++;
	}
	return (0);
}

static int	add_empty_env_var(char ***envp, const char *key)
{
	int		count;
	int		i;
	char	**new_env;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < count)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[count] = ft_strdup(key);
	if (!new_env[count])
		return (free(new_env), 1);
	new_env[count + 1] = NULL;
	replace_env_array(envp, new_env);
	return (0);
}

int	ensure_env_var(char ***envp, const char *key)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	if (env_var_exists(envp, key, key_len))
		return (0);
	return (add_empty_env_var(envp, key));
}

int	update_underscore_var(char ***envp, char *last_arg)
{
	if (!last_arg)
		return (0);
	return (set_env_var_cd(envp, "_", last_arg));
}
