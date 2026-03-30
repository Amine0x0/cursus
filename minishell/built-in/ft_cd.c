/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:16:04 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 22:20:25 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static char	*get_env_value2(const char *name, char **envp)
{
	int		i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

int	cd_to_home(char ***envp)
{
	char	*home;
	char	cwd[PATH_MAX];

	home = get_env_value2("HOME", *envp);
	if (!home)
	{
		print_error("cd: HOME not set\n", NULL);
		return (1);
	}
	if (chdir(home) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env_var_cd(envp, "PWD", cwd);
	else
		set_env_var_cd(envp, "PWD", home);
	return (0);
}

int	handle_getcwd_error(char ***envp)
{
	char	*current_pwd;
	char	*new_pwd;

	print_err("cd: error retrieving current directory: getcwd: "
		"cannot access parent directories: No such file or directory\n", NULL);
	current_pwd = get_env_value2("PWD", *envp);
	if (!current_pwd)
		return (1);
	new_pwd = ft_strjoin(current_pwd, "/..");
	if (!new_pwd)
		return (1);
	set_env_var_cd(envp, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

int	handle_cd_dotdot_deleted_dir(char ***envp)
{
	char	cwd[PATH_MAX];

	if (chdir("..") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			set_env_var_cd(envp, "PWD", cwd);
			return (0);
		}
		else
			return (handle_getcwd_error(envp));
	}
	else
	{
		perror("cd");
		return (1);
	}
}

int	builtin_cd(char **args, char ***envp)
{
	char	*old_pwd;
	int		special_result;

	old_pwd = get_env_value2("PWD", *envp);
	if (old_pwd)
		set_env_var_cd(envp, "OLDPWD", old_pwd);
	special_result = handle_special_args(args, envp);
	if (special_result != -1)
		return (special_result);
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (update_pwd_and_oldpwd(envp, args[1]));
}
