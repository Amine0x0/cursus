/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 22:23:05 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 22:23:06 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static char	*get_env_value(const char *name, char **envp)
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

int	handle_special_args(char **args, char ***envp)
{
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (cd_to_home(envp));
	else if (ft_strcmp(args[1], "..") == 0)
		return (handle_cd_dotdot_deleted_dir(envp));
	return (-1);
}

int	build_relative_path(char ***envp, char *target_dir)
{
	char	*current_pwd;
	char	*resolved_target;
	size_t	total_len;

	current_pwd = get_env_value("PWD", *envp);
	if (!current_pwd)
		return (1);
	total_len = ft_strlen(current_pwd) + ft_strlen(target_dir) + 2;
	resolved_target = malloc(total_len);
	if (!resolved_target)
		return (1);
	ft_strlcpy(resolved_target, current_pwd, ft_strlen(current_pwd) + 1);
	ft_strlcat(resolved_target, "/", total_len);
	ft_strlcat(resolved_target, target_dir, total_len);
	set_env_var_cd(envp, "PWD", resolved_target);
	free(resolved_target);
	return (0);
}

int	handle_getcwd_failure(char ***envp, char *target_dir)
{
	if (!target_dir)
		return (0);
	if (target_dir[0] == '/')
	{
		set_env_var_cd(envp, "PWD", target_dir);
		return (0);
	}
	return (build_relative_path(envp, target_dir));
}

int	update_pwd_and_oldpwd(char ***envp, char *target_dir)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	old_pwd = get_env_value("PWD", *envp);
	if (old_pwd)
		set_env_var_cd(envp, "OLDPWD", old_pwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		set_env_var_cd(envp, "PWD", cwd);
	else
		return (handle_getcwd_failure(envp, target_dir));
	return (0);
}
