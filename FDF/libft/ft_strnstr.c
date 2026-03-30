/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 03:50:48 by amabbadi          #+#    #+#             */
/*   Updated: 2024/11/16 17:40:42 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	l_needle;
	char	*ptr;

	l_needle = ft_strlen(needle);
	ptr = (char *)haystack;
	if (!needle || *needle == '\0')
		return (ptr);
	while (*ptr && len > 0)
	{
		if (ft_strncmp(ptr, needle, l_needle) == 0 && l_needle <= len)
			return (ptr);
		ptr++;
		len--;
	}
	return (0);
}
