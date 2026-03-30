/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 00:35:50 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/09 00:35:51 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static char	*get_env_value(char *var_name, char **envp)
{
	int		i;
	int		len;
	char	*env_var;

	if (!var_name || !envp)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
		{
			env_var = ft_strdup(envp[i] + len + 1);
			return (env_var);
		}
		i++;
	}
	return (NULL);
}

static char	*var_value(char *str, int *i, char **envp)
{
	int		start;
	char	*var_name;
	char	*var_value;
	char	*result;

	start = *i;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	var_value = get_env_value(var_name, envp);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	result = ft_strdup(var_value);
	free(var_value);
	return (result);
}

static char	*handle_special_vars(char *str, int *i, int exit_status)
{
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(exit_status));
	}
	else if (str[*i] == '0')
	{
		(*i)++;
		return (ft_strdup("minishell"));
	}
	else if (ft_isdigit(str[*i]))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	return (NULL);
}

char	*expand_odd_dollar(char *str, int *i, char **envp, int exit_status)
{
	char	*expanded;
	char	*result;

	expanded = handle_special_vars(str, i, exit_status);
	if (!expanded)
	{
		if (!ft_isalnum(str[*i]) && str[*i] != '_')
			expanded = ft_strdup("$");
		else
			expanded = var_value(str, i, envp);
	}
	result = ft_strdup(expanded);
	free(expanded);
	return (result);
}
