/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:39:43 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 04:17:40 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	is_valid_identifier(const char *key)
{
	int	i;

	if (!key || !*key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
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

int	builtin_export(char **args, char ***envp)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	if (!args[1])
	{
		print_env_vars(*envp);
		return (0);
	}
	while (args[i])
	{
		ret = process_export_arg(args[i], envp, ret);
		i++;
	}
	return (ret);
}
