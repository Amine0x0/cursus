/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:39:52 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 10:41:44 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	is_protected_var(const char *var)
{
	return (ft_strcmp(var, "_") == 0);
}

static int	is_valid_unset_identifier(const char *key)
{
	int	i;

	if (!key || !*key || (!ft_isalpha(key[0]) && key[0] != '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	shift_env(char ***envp, int index, int count)
{
	int	j;

	free((*envp)[index]);
	j = index;
	while (j < count - 1)
	{
		(*envp)[j] = (*envp)[j + 1];
		j++;
	}
	(*envp)[count - 1] = NULL;
}

static int	remove_env_var(char ***envp, char *var)
{
	int	i;
	int	count;

	if (!envp || !*envp || !var)
		return (0);
	if (is_protected_var(var))
		return (0);
	count = 0;
	while ((*envp)[count])
		count++;
	i = 0;
	while (i < count)
	{
		if (is_env_var((*envp)[i], var))
		{
			shift_env(envp, i, count);
			return (0);
		}
		i++;
	}
	return (0);
}

int	builtin_unset(char **args, char ***envp)
{
	int	i;
	int	ret;

	if (!args[1])
		return (0);
	i = 1;
	ret = 0;
	while (args[i])
	{
		if (!is_valid_unset_identifier(args[i]))
		{
			print_err("unset: '%s': not a valid identifier\n", args[i]);
			ret = 1;
		}
		else
		{
			remove_env_var(envp, args[i]);
		}
		i++;
	}
	return (ret);
}
