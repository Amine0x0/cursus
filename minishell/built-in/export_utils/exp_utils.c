/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:23:13 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 04:23:22 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

int	process_export_arg(char *arg, char ***envp, int ret)
{
	t_export_data	data;

	parse_export_arg(arg, &data.key, &data.value, &data.is_append);
	data.has_equal = ft_strchr(arg, '=') != NULL;
	if (!data.key || !*data.key)
	{
		print_err("minishell: export: `%s': not a valid identifier\n",
			arg);
		ret = 1;
		if (data.key)
			free(data.key);
		if (data.value)
			free(data.value);
		return (ret);
	}
	data.found = update_existing_var(envp, data.key, data.value,
			data.is_append);
	if (!data.found)
		add_new_var(envp, data.key, data.value, data.has_equal);
	else
		cleanup_export_data(&data);
	return (ret);
}

void	cleanup_export_data(t_export_data *data)
{
	free(data->key);
	if (data->value)
		free(data->value);
}
