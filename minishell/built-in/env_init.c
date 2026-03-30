/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:38:59 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 03:04:54 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	**initialize_default_env(void)
{
	char	**env;

	env = malloc(sizeof(char *) * 5);
	if (!env)
		return (NULL);
	env[0] = get_default_path();
	env[1] = get_default_pwd();
	env[2] = get_default_shlvl();
	env[3] = get_default_oldpwd();
	env[4] = NULL;
	if (!env[0] || !env[1] || !env[2] || !env[3])
	{
		free_env(env);
		return (NULL);
	}
	return (env);
}

static int	append_oldpwd(char ***envp, int count)
{
	char	**new_env;
	char	**old_env;
	int		i;

	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < count)
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[count] = ft_strdup("OLDPWD");
	if (!new_env[count])
		return (free(new_env), 1);
	new_env[count + 1] = NULL;
	old_env = *envp;
	*envp = new_env;
	free(old_env);
	return (0);
}

static int	ensure_oldpwd_exists(char ***envp)
{
	int	i;
	int	count;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], "OLDPWD", 6) == 0 && ((*envp)[i][6] == '='
				|| (*envp)[i][6] == '\0'))
			return (0);
		i++;
	}
	count = 0;
	while ((*envp)[count])
		count++;
	return (append_oldpwd(envp, count));
}

char	**setup_environment(char **original_env)
{
	char	**my_env;

	if (!original_env || !original_env[0])
	{
		my_env = initialize_default_env();
	}
	else
	{
		my_env = dup_env(original_env);
		if (my_env)
		{
			increment_shlvl(my_env);
			ensure_oldpwd_exists(&my_env);
		}
	}
	return (my_env);
}
