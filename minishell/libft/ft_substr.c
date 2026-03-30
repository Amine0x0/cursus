/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:41:52 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/02 15:56:26 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		str = (char *)malloc(1);
		if (str)
			str[0] = '\0';
		return (str);
	}
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
