/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:34:44 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/04 10:50:39 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtin(char **args, char ***envp)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, envp));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(*envp));
	else if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(*envp));
	else if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, envp));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, envp));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	return (1);
}
