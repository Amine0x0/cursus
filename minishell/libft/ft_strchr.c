/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:47:30 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/02 15:55:39 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c && *s)
		return ((char *)s);
	if ((char)c == '\0')
		return ((char *)s);
	else
		return (NULL);
}
