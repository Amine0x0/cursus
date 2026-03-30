/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:32:48 by amabbadi          #+#    #+#             */
/*   Updated: 2025/02/06 21:32:49 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

static int	countword(char *str, char c)
{
	int	inword;
	int	count;

	if (!str)
		return (0);
	inword = 0;
	count = 0;
	while (*str)
	{
		if (!inword && *str != c)
		{
			inword = 1;
			count++;
		}
		if (inword && *str == c)
			inword = 0;
		str++;
	}
	return (count);
}

static int	delen(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	allocate_word(char **split, char *s, int word_len, int i)
{
	split[i] = (char *)malloc((word_len + 1) * sizeof(char));
	if (!split[i])
	{
		while (i > 0)
			free(split[--i]);
		free(split);
		return (0);
	}
	ft_strlcpy(split[i], s, word_len + 1);
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		word_count;
	int		i;
	int		word_len;

	if (!s)
		return (NULL);
	i = 0;
	word_count = countword((char *)s, c);
	split = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (i < word_count)
	{
		while (*s && *s == c)
			s++;
		word_len = delen((char *)s, c);
		if (!allocate_word(split, (char *)s, word_len, i))
			return (NULL);
		s += word_len;
		i++;
	}
	split[i] = NULL;
	return (split);
}
