/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:49:35 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 17:53:01 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*get_last_arg(char **args)
{
	int	i;

	i = 0;
	if (!args || !args[0])
		return (NULL);
	while (args[i])
		i++;
	return (args[i - 1]);
}

int	count_commands(t_cmd *commands)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = commands;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	close_all_pipes(int *pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i]);
		i++;
	}
}
