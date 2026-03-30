/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:39:36 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 10:51:03 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	builtin_env(char **envp)
{
	int	i;

	if (!envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
