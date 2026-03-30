/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:43:18 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/04 17:44:09 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	execute_commands(t_cmd *commands, char ***envp, int *exit_status)
{
	int	cmd_count;

	if (!commands)
		return (0);
	cmd_count = count_commands(commands);
	if (cmd_count == 1)
	{
		*exit_status = exec_simple_command(commands, envp, *exit_status);
		return (*exit_status);
	}
	*exit_status = execute_pipeline(commands, envp, exit_status);
	return (*exit_status);
}
