/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:54:43 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/26 04:54:44 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

static int	is_newline(char **unprocessed, char **oneline)
{
	char	*temp;

	if (*unprocessed && ft_strchr(*unprocessed, '\n'))
	{
		*oneline = ft_substr(*unprocessed, 0, len(*unprocessed, '\n') + 1);
		if (!*oneline)
		{
			free(*unprocessed);
			*unprocessed = NULL;
			return (0);
		}
		temp = *unprocessed;
		*unprocessed = ft_substr(temp, len(temp, '\n') + 1, ft_strlen(temp)
				- len(temp, '\n') - 1);
		free(temp);
		if (!*unprocessed)
			return (0);
		return (1);
	}
	return (2);
}

static void	handle_read_error(char **unprocessed, ssize_t readlen)
{
	if (readlen < 0)
	{
		free(*unprocessed);
		*unprocessed = NULL;
	}
}

static int	main_loop(char **unprocessed, char **oneline, int fd)
{
	char	*buffer;
	char	*temp;
	ssize_t	readlen;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	while (1)
	{
		if (is_newline(unprocessed, oneline) != 2)
			return (free(buffer), 0);
		readlen = read(fd, buffer, BUFFER_SIZE);
		if (readlen <= 0)
		{
			handle_read_error(unprocessed, readlen);
			return (free(buffer), 0);
		}
		buffer[readlen] = '\0';
		temp = *unprocessed;
		*unprocessed = ft_strjoin(temp, buffer);
		free(temp);
		if (!*unprocessed)
			return (free(buffer), 0);
	}
}

char	*get_next_line(int fd)
{
	static char	*unprocessed;
	char		*oneline;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	oneline = NULL;
	if (main_loop(&unprocessed, &oneline, fd) == -1)
	{
		free(unprocessed);
		unprocessed = NULL;
		return (NULL);
	}
	if (!oneline && unprocessed && *unprocessed)
	{
		oneline = ft_strdup(unprocessed);
		free(unprocessed);
		unprocessed = NULL;
	}
	if (!oneline && unprocessed)
	{
		free(unprocessed);
		unprocessed = NULL;
	}
	return (oneline);
}
