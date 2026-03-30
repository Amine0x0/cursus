/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:54:06 by ylabser           #+#    #+#             */
/*   Updated: 2025/08/02 15:54:39 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

static int	count_nbr(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		len;
	long	nb;

	nb = n;
	len = count_nbr(nb);
	if (n < 0)
	{
		nb *= -1;
		len++;
	}
	arr = (char *)malloc(len + 1);
	if (!arr)
		return (NULL);
	if (n == 0)
		arr[0] = '0';
	arr[len] = '\0';
	while (len-- && nb != 0)
	{
		arr[len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		arr[0] = '-';
	return (arr);
}
