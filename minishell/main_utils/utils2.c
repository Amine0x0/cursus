/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:07:47 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 04:07:51 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	handle_tokens(char *line, t_shell_data *shell_data)
{
	t_token			*tokens;
	t_cmd			*commands;
	t_process_data	data;
	int				should_continue;
	t_exec_data		exec_data;

	tokens = get_tokens(line);
	if (!tokens)
		return (2);
	data = (t_process_data){tokens, shell_data->my_envp,
		shell_data->exit_status, line};
	should_continue = 0;
	commands = process_tokens(&data, &should_continue);
	if (!commands)
		return (should_continue);
	exec_data = (t_exec_data){&shell_data->my_envp, tokens, line, 0};
	if (execute_shell_command(commands, &exec_data) == 1)
		return (-1);
	shell_data->exit_status = exec_data.exit_status;
	return (0);
}

t_cmd	*process_tokens(t_process_data *data, int *should_continue)
{
	t_cmd	*commands;

	if (!check_syntax(data->tokens))
	{
		free_tokens(data->tokens);
		free(data->line);
		*should_continue = 2;
		return (NULL);
	}
	expand_tokens(data->tokens, data->my_envp, data->exit_status);
	if (!check_non_empty_tokens(data->tokens))
	{
		free_tokens(data->tokens);
		free(data->line);
		*should_continue = 0;
		return (NULL);
	}
	commands = parse_tokens(data->tokens);
	if (!commands)
	{
		(free_tokens(data->tokens), free(data->line));
		*should_continue = 2;
		return (NULL);
	}
	return (commands);
}
