/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 01:07:52 by amabbadi          #+#    #+#             */
/*   Updated: 2024/11/16 17:40:24 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	if (!src && !dst)
		return (0);
	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	while (n > 0)
	{
		*pdst++ = *psrc++;
		n--;
	}
	return (dst);
}
