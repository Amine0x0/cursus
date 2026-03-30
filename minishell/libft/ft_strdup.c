/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:06:51 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/02 15:55:52 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*ft_strdup(const char *src)
{
	char	*p;
	int		i;

	p = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
