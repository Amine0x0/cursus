/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:22:51 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 04:35:09 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

static char	*create_new_entry(char *key, char *value)
{
	char	*new_entry;
	size_t	key_len;

	key_len = ft_strlen(key);
	new_entry = malloc(key_len + ft_strlen(value) + 2);
	if (!new_entry)
		return (NULL);
	ft_strlcpy(new_entry, key, key_len + 1);
	new_entry[key_len] = '=';
	ft_strlcpy(new_entry + key_len + 1, value, ft_strlen(value) + 1);
	return (new_entry);
}

static int	handle_append_update(char ***envp, int i, char *key, char *value)
{
	size_t	key_len;
	char	*old_val;
	char	*new_val;
	char	*new_entry;

	key_len = ft_strlen(key);
	if ((*envp)[i][key_len] == '=')
	{
		old_val = ft_strdup((*envp)[i] + key_len + 1);
		new_val = ft_strjoin(old_val, value);
		free(old_val);
		new_entry = create_new_entry(key, new_val);
		free(new_val);
		if (!new_entry)
			return (1);
		(free((*envp)[i]), (*envp)[i] = new_entry);
	}
	else
	{
		new_entry = create_new_entry(key, value);
		if (!new_entry)
			return (1);
		(free((*envp)[i]), (*envp)[i] = new_entry);
	}
	return (0);
}

static int	apply_update(t_update_data *data)
{
	char	*new_entry;

	if (data->is_append && data->value)
	{
		if (handle_append_update(data->envp, data->i, data->key, data->value))
			return (1);
	}
	else if (data->value)
	{
		new_entry = create_new_entry(data->key, data->value);
		if (!new_entry)
			return (1);
		free((*data->envp)[data->i]);
		(*data->envp)[data->i] = new_entry;
	}
	return (0);
}

int	update_existing_var(char ***envp, char *key, char *value, int is_append)
{
	int				i;
	size_t			key_len;
	t_update_data	data;

	i = -1;
	key_len = ft_strlen(key);
	while ((*envp)[++i])
	{
		if (ft_strncmp((*envp)[i], key, key_len) == 0
			&& ((*envp)[i][key_len] == '=' || (*envp)[i][key_len] == '\0'))
		{
			data = (t_update_data){envp, i, key, value, is_append};
			if (apply_update(&data))
				return (1);
			return (1);
		}
	}
	return (0);
}
