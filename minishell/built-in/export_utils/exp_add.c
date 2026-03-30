/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:22:48 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 04:29:18 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../mini.h"

char	*create_env_entry(char *key, char *value, int has_equal)
{
	char	*entry;
	size_t	key_len;
	size_t	val_len;

	key_len = ft_strlen(key);
	if (value || has_equal)
	{
		if (value)
			val_len = ft_strlen(value);
		else
			val_len = 0;
		entry = malloc(key_len + val_len + 2);
		if (!entry)
			return (NULL);
		ft_strlcpy(entry, key, key_len + 1);
		entry[key_len] = '=';
		if (value)
			ft_strlcpy(entry + key_len + 1, value, val_len + 1);
		else
			entry[key_len + 1] = '\0';
	}
	else
		entry = ft_strdup(key);
	return (entry);
}
