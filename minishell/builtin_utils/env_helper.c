/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 03:30:43 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/12 07:08:20 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	append_new_entry(char ***envp, char *new_entry)
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
		new_env[i] = ft_strdup((*envp)[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			return (free(new_env), 1);
		}
		i++;
	}
	new_env[count] = new_entry;
	new_env[count + 1] = NULL;
	return (replace_env_array(envp, new_env), 0);
}

int	update_if_exists(char ***envp, char *name, char *new_entry)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (is_env_var((*envp)[i], name))
		{
			free((*envp)[i]);
			(*envp)[i] = new_entry;
			return (1);
		}
		i++;
	}
	return (0);
}

void	replace_env_array(char ***envp, char **new_env)
{
	char	**old_env;

	if (!envp)
		return ;
	old_env = *envp;
	*envp = new_env;
	if (old_env)
		free_env(old_env);
}

int	is_env_var(const char *env, const char *name)
{
	size_t	name_len;

	name_len = ft_strlen(name);
	return (ft_strncmp(env, name, name_len) == 0 && (env[name_len] == '='
			|| env[name_len] == '\0'));
}

char	*create_env_entry_basic(char *name, char *value)
{
	size_t	name_len;
	size_t	value_len;
	char	*new_entry;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	new_entry = malloc(name_len + value_len + 2);
	if (!new_entry)
		return (NULL);
	ft_strlcpy(new_entry, name, name_len + 1);
	new_entry[name_len] = '=';
	ft_strlcpy(new_entry + name_len + 1, value, value_len + 1);
	return (new_entry);
}
