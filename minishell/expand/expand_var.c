/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:30:01 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/05 06:21:29 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	count_dollars(char *str, int *i)
{
	int	count;

	count = 1;
	(*i)++;
	while (str[*i] == '$')
	{
		count++;
		(*i)++;
	}
	return (count);
}

char	*expand_var(char *str, int *i, char **envp, int exit_status)
{
	int		dollar_count;
	char	*result;
	int		pair_count;
	char	*expanded_part;

	result = NULL;
	dollar_count = count_dollars(str, i);
	pair_count = dollar_count / 2;
	result = ft_strdup("");
	while (pair_count--)
		result = ft_strjoin_free(result, "", 1);
	if (dollar_count % 2 == 1)
	{
		expanded_part = expand_odd_dollar(str, i, envp, exit_status);
		result = ft_strjoin_free(result, expanded_part, 1);
		free(expanded_part);
	}
	return (result);
}
