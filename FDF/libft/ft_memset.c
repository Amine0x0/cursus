/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 00:54:44 by amabbadi          #+#    #+#             */
/*   Updated: 2024/11/16 17:40:26 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int value, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)b;
	while (len > 0)
	{
		*ptr++ = (unsigned char)value;
		len--;
	}
	return (b);
}
