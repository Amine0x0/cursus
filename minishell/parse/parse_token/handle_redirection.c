/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:08:01 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/04 17:17:43 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

static int	add_redic(t_cmd *cmd, t_token *redirect, char *file)
{
	t_redirection	*last;
	t_redirection	*new;

	new = malloc(sizeof(t_redirection));
	if (!new)
		return (0);
	new->type = redirect->type;
	new->file = ft_strdup(file);
	if (!new->file)
		return (free(new), 0);
	new->next = NULL;
	if (!cmd->redirections)
		cmd->redirections = new;
	else
	{
		last = cmd->redirections;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (1);
}

char	*process_heredoc_delimiter(char *raw_delimiter, int quoted)
{
	char	*processed;
	int		i;
	int		j;

	if (!quoted)
		return (ft_strdup(raw_delimiter));
	processed = malloc(ft_strlen(raw_delimiter) + 1);
	if (!processed)
		return (NULL);
	i = 0;
	j = 0;
	while (raw_delimiter[i])
	{
		if (raw_delimiter[i] == '"' || raw_delimiter[i] == '\'')
		{
			i++;
			continue ;
		}
		processed[j++] = raw_delimiter[i++];
	}
	processed[j] = '\0';
	return (processed);
}

static t_heredoc	*create_heredoc_node(char *delimiter, int quoted)
{
	t_heredoc	*new_hd;
	char		*processed_delimiter;

	new_hd = malloc(sizeof(t_heredoc));
	if (!new_hd)
		return (NULL);
	processed_delimiter = process_heredoc_delimiter(delimiter, quoted);
	if (!processed_delimiter)
	{
		free(new_hd);
		return (NULL);
	}
	new_hd->delimiter = processed_delimiter;
	new_hd->quoted = quoted;
	new_hd->fd = -1;
	new_hd->next = NULL;
	return (new_hd);
}

static int	add_heredoc(t_cmd *cmd, char *delimiter, int quoted)
{
	t_heredoc	*new_hd;
	t_heredoc	*current;

	if (!cmd || !delimiter)
		return (0);
	new_hd = create_heredoc_node(delimiter, quoted);
	if (!new_hd)
		return (0);
	if (!cmd->heredocs)
		cmd->heredocs = new_hd;
	else
	{
		current = cmd->heredocs;
		while (current->next)
			current = current->next;
		current->next = new_hd;
	}
	return (1);
}

int	handle_redirection(t_cmd *cmd, t_token **current)
{
	t_token	*redirect;
	t_token	*file;

	redirect = *current;
	file = redirect->next;
	if (!file || file->type != TOKEN_WORD)
		return (0);
	if (redirect->type == TOKEN_HEREDOC)
	{
		if (!add_heredoc(cmd, file->value, file->quoted))
			return (0);
		*current = file->next;
		return (1);
	}
	else
	{
		if (!add_redic(cmd, redirect, file->value))
			return (0);
		*current = file->next;
		return (1);
	}
}
