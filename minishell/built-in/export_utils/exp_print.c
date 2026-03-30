/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:23:10 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 04:23:11 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

static void	sort_env_array(char **sorted, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
			{
				tmp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_sorted_vars(char **sorted, int count)
{
	int		i;
	char	*eq;

	i = 0;
	while (i < count)
	{
		eq = ft_strchr(sorted[i], '=');
		if (eq)
		{
			write(1, "declare -x ", 11);
			write(1, sorted[i], eq - sorted[i]);
			write(1, "=\"", 2);
			write(1, eq + 1, ft_strlen(eq + 1));
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, "declare -x ", 11);
			write(1, sorted[i], ft_strlen(sorted[i]));
			write(1, "\n", 1);
		}
		i++;
	}
}

void	print_env_vars(char **envp)
{
	int		count;
	char	**sorted;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	if (count == 0)
		return ;
	sorted = malloc(sizeof(char *) * (count + 1));
	if (!sorted)
		return ;
	i = 0;
	while (i < count)
	{
		sorted[i] = envp[i];
		i++;
	}
	sorted[count] = NULL;
	sort_env_array(sorted, count);
	print_sorted_vars(sorted, count);
	free(sorted);
}
