/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:01:56 by amabbadi          #+#    #+#             */
/*   Updated: 2024/11/16 18:25:14 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lens;
	size_t	lend;
	size_t	i;
	size_t	j;

	lens = ft_strlen(src);
	lend = ft_strlen(dst);
	i = 0;
	j = lend;
	if (dstsize <= lend || dstsize == 0)
		return (dstsize + lens);
	while (src[i] && lend + i < dstsize - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (lens + lend);
}
