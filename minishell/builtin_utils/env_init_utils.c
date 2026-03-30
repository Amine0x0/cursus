/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 03:07:22 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 03:34:49 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*get_default_path(void)
{
	char	*result;

	result = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	if (!result)
		return (NULL);
	return (result);
}

char	*get_default_pwd(void)
{
	char	cwd[PATH_MAX];
	char	*pwd_str;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_strdup("PWD=/"));
	pwd_str = malloc(ft_strlen(cwd) + 5);
	if (!pwd_str)
		return (NULL);
	ft_strlcpy(pwd_str, "PWD=", 5);
	ft_strlcat(pwd_str, cwd, ft_strlen(cwd) + 5);
	return (pwd_str);
}

char	*get_default_shlvl(void)
{
	return (ft_strdup("SHLVL=1"));
}

char	*get_default_oldpwd(void)
{
	return (ft_strdup("OLDPWD"));
}
