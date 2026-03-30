/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 03:57:50 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/12 07:07:34 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char	*get_shell_line(void)
{
	char	*line;

	line = readline("minishell> ");
	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (!*line)
	{
		free(line);
		return ("");
	}
	add_history(line);
	return (line);
}

static void	cleanup_resources(t_cmd *commands, t_token *tokens, char *line)
{
	free_commands(commands);
	free_tokens(tokens);
	free(line);
}

int	execute_shell_command(t_cmd *commands, t_exec_data *exec_data)
{
	exec_data->exit_status = execute_commands(commands, exec_data->envp,
			&exec_data->exit_status);
	if (exec_data->exit_status == 130)
	{
		cleanup_resources(commands, exec_data->tokens, exec_data->line);
		return (1);
	}
	cleanup_resources(commands, exec_data->tokens, exec_data->line);
	return (0);
}

static int	shell_loop(char ***my_envp, char **envp)
{
	char			*line;
	t_shell_data	shell_data;
	int				result;

	shell_data.exit_status = 0;
	(void)envp;
	while (1)
	{
		line = get_shell_line();
		if (!line)
			break ;
		if (line[0] == '\0')
			continue ;
		shell_data.my_envp = *my_envp;
		result = handle_tokens(line, &shell_data);
		if (result == -1)
			continue ;
		if (result != 0)
			shell_data.exit_status = result;
		*my_envp = shell_data.my_envp;
	}
	return (shell_data.exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	char	**my_envp;
	int		exit_status;

	(void)argc;
	(void)argv;
	if (!isatty(STDIN_FILENO))
		return (1);
	if (initialize_shell(envp, &my_envp))
		return (1);
	msh_signals();
	exit_status = shell_loop(&my_envp, envp);
	free_env(my_envp);
	return (exit_status);
}
