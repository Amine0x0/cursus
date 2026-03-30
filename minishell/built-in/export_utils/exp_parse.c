/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:23:03 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 04:23:04 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

static void	handle_append_case(char *arg, char *append_pos, char **key,
		char **value)
{
	*key = ft_substr(arg, 0, append_pos - arg);
	if (*key && is_valid_identifier(*key))
		*value = ft_strdup(append_pos + 2);
	else
	{
		free(*key);
		*key = NULL;
	}
}

static void	handle_equal_case(char *arg, char *eq, char **key, char **value)
{
	*key = ft_substr(arg, 0, eq - arg);
	if (*key && is_valid_identifier(*key))
		*value = ft_strdup(eq + 1);
	else
	{
		free(*key);
		*key = NULL;
	}
}

void	parse_export_arg(char *arg, char **key, char **value, int *is_append)
{
	char	*eq;
	char	*append_pos;

	*key = NULL;
	*value = NULL;
	*is_append = 0;
	eq = ft_strchr(arg, '=');
	append_pos = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (append_pos && (!eq || append_pos < eq))
	{
		*is_append = 1;
		handle_append_case(arg, append_pos, key, value);
	}
	else if (eq)
		handle_equal_case(arg, eq, key, value);
	else
	{
		if (is_valid_identifier(arg))
			*key = ft_strdup(arg);
	}
}
