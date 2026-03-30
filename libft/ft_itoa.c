/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <amabbadi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:19:02 by amabbadi          #+#    #+#             */
/*   Updated: 2024/11/16 17:40:13 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	long	num;
	int		len;

	num = (long)n;
	len = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num > 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	num;
	int		len;
	char	*str;

	num = (long)n;
	len = num_len(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	while (len > 0 && num != 0)
	{
		str[--len] = (num % 10) + '0';
		num /= 10;
	}
	if (n == 0)
		str[0] = '0';
	return (str);
}
