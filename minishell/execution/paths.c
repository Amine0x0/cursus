/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:55:03 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 06:18:17 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*search_in_paths(char *cmd, char **paths)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
		{
			i++;
			continue ;
		}
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
		{
			i++;
			continue ;
		}
		if (access(full_path, F_OK) == 0)
			return (full_path);
		(free(full_path), i++);
	}
	return (NULL);
}

static char	*try_local_path(char *cmd)
{
	char	*local_path;

	local_path = ft_strjoin("./", cmd);
	if (local_path)
	{
		if (access(local_path, F_OK | X_OK) == 0)
			return (local_path);
		free(local_path);
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	path_env = get_path_env(envp);
	if (!path_env || !*path_env)
		return (try_local_path(cmd));
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	full_path = search_in_paths(cmd, paths);
	i = 0;
	while (paths[i])
		(free(paths[i]), i++);
	return (free(paths), full_path);
}
