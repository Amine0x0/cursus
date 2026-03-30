/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 11:39:33 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/03 11:39:34 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	is_n_flag(const char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

int	builtin_echo(char **args)
{
	int	no_newline;
	int	i;
	int	first;

	if (!args)
		return (printf("\n"), 0);
	no_newline = 0;
	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		no_newline = 1;
		i++;
	}
	first = 1;
	while (args[i])
	{
		if (!first)
			printf(" ");
		printf("%s", args[i]);
		first = 0;
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
