/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolkit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 16:45:22 by amabbadi          #+#    #+#             */
/*   Updated: 2025/03/22 16:45:24 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	clean(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**find_env_path(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
	{
		ft_printf("PATH environment variable not found\n");
		return (NULL);
	}
	paths = ft_split(envp[i] + 5, ':');
	if (!paths || !paths[0])
	{
		ft_printf("PATH environment variable is empty\n");
		if (paths)
			clean(paths);
		return (NULL);
	}
	return (paths);
}

char	*check_paths(char *cmd, char **paths)
{
	char	*path;
	char	*part_path;
	int		i;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		if (!part_path)
			return (clean(paths), NULL);
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (!path)
			return (clean(paths), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*path(char *cmd, char **envp)
{
	char	**paths;
	char	*result;
	char	*abs;

	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
	{
		abs = ft_strdup(cmd);
		if (!abs)
			return (NULL);
		return (abs);
	}
	paths = find_env_path(envp);
	if (!paths)
		return (NULL);
	result = check_paths(cmd, paths);
	if (result == NULL)
		return (clean(paths), NULL);
	clean(paths);
	return (result);
}

int	exec(char *argv, char **envp)
{
	char	**cmd;
	char	*correct_path;

	if (!argv || !*argv)
		return (ft_printf("Empty command\n"), -1);
	cmd = ft_split(argv, ' ');
	if (!cmd)
		return (ft_printf("ft_split failed"), -1);
	if (!cmd[0])
		(clean(cmd), ft_printf("%s: Command not found\n", argv), exit(127));
	correct_path = path(cmd[0], envp);
	if (!correct_path)
		(clean(cmd), ft_printf("%s: Command not found\n", argv), exit(127));
	if (execve(correct_path, cmd, envp) == -1)
		(perror("Exec failed"), free(correct_path), clean(cmd), exit(1));
	return (-1);
}
