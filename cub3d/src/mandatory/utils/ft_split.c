/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 04:55:14 by amabbadi          #+#    #+#             */
/*   Updated: 2025/12/26 04:55:15 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	cw(char const *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			j++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (j);
}

static int	cc(char const *str, char c, int j)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == c && j == 2)
		i++;
	while (str[i] && str[i] != c && j == 1)
		i++;
	return (i);
}

static char	*copy(char const *s, char c, int i)
{
	char	*dest;
	int		j;
	int		len;

	j = 0;
	len = cc(&s[i], c, 1);
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (j < len && s[i] != '\0')
	{
		dest[j] = s[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

void	*free_split(char **strs, int i)
{
	if (!strs)
		return (NULL);
	if (i == -1)
	{
		i = 0;
		while (strs[i])
			i++;
	}
	while (i > 0)
	{
		i--;
		free(strs[i]);
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**strs;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (cw(s, c) + 1));
	if (!strs)
		return (NULL);
	while (j < cw(s, c))
	{
		i += cc(&s[i], c, 2);
		strs[j] = copy(s, c, i);
		i += cc(&s[i], c, 1);
		if (strs[j] == NULL)
			return (free_split(strs, j));
		j++;
	}
	strs[j] = NULL;
	return (strs);
}
