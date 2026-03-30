/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 03:38:19 by amabbadi          #+#    #+#             */
/*   Updated: 2025/08/05 03:38:20 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	**dup_env(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	free_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	close_extra_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void	print_err(const char *format, const char *arg)
{
	const char	*p;

	p = format;
	if (!arg)
	{
		write(2, format, ft_strlen(format));
		return ;
	}
	while (*p)
	{
		if (*p == '%' && *(p + 1) == 's')
		{
			write(2, arg, ft_strlen(arg));
			p += 2;
		}
		else
		{
			write(2, p, 1);
			p++;
		}
	}
}
